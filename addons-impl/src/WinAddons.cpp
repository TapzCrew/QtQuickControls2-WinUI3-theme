#include "WinAddons.mpp"

#include <dwmapi.h>
#include <winreg.h>

#include <QDebug>

static constexpr auto DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1 = DWORD { 19 };
static constexpr auto DWMWA_MICA_EFFECT                         = DWORD { 1029 };

extern "C" {
// 1809
auto ShouldSystemUseDarkThemePolyfill() -> bool {
    auto value      = DWORD { 1 };
    auto value_size = DWORD { sizeof(value) };
    if (RegGetValueW(HKEY_CURRENT_USER,
                     LR"(Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)",
                     L"SystemUsesLightTheme",
                     RRF_RT_REG_DWORD,
                     nullptr,
                     &value,
                     &value_size) != ERROR_SUCCESS)
        value = 1;
    return value != 0;
}
}

/////////////////////////////////////
/////////////////////////////////////
WinAddons::WinAddons(HWND hwnd)
    : m_handle { hwnd }, m_is_dark_mode_supported { false }, m_is_dark_mode_enabled { false },
      m_is_mica_supported { false } {
    Q_ASSERT(m_handle);

    m_ntdll.setFileName("ntdll.dll");

    Q_ASSERT(m_ntdll.load());

    m_user32.setFileName("user32.dll");

    Q_ASSERT(m_user32.load());

    m_uxtheme.setFileName("uxtheme.dll");

    loadFunctions();

    m_is_mica_supported = m_windows_version.build_number >= 22000;

    if (m_is_dark_mode_supported) {
        allowDarkMode(false);
        m_RefreshImmersiveColorPolicyState();
    }
}

/////////////////////////////////////
/////////////////////////////////////
WinAddons::~WinAddons() = default;

/////////////////////////////////////
/////////////////////////////////////
auto WinAddons::setMicaEnabled(bool enabled) -> void {
    if (!m_is_mica_supported) return;

    if (m_windows_version.build_number < 22621) {
        const auto use_mica = BOOL { enabled };
        ::DwmSetWindowAttribute(m_handle, DWMWA_MICA_EFFECT, &use_mica, sizeof(use_mica));
    } else {
        const auto type = (enabled) ? DWMSBT_MAINWINDOW : DWMSBT_NONE;
        ::DwmSetWindowAttribute(m_handle, DWMWA_SYSTEMBACKDROP_TYPE, &type, sizeof(type));
    }
}

/////////////////////////////////////
/////////////////////////////////////
auto WinAddons::setDarkModeEnabled(bool enabled) -> void {
    if (!isDarkModeSupported()) return;

    const auto attribute = (m_windows_version.build_number >= 18970)
                               ? DWORD { DWMWA_USE_IMMERSIVE_DARK_MODE }
                               : DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1;

    auto value = BOOL { enabled };

    ::DwmSetWindowAttribute(m_handle, attribute, &value, sizeof(value));

    if (m_windows_version.build_number < 18362)
        ::SetPropW(m_handle,
                   L"UseImmersiveDarkModeColors",
                   reinterpret_cast<HANDLE>(static_cast<INT_PTR>(value)));
    else {
        auto data = WindowCompositionAttribData { WindowCompositionAttrib::UseDarkModeColors,
                                                  &value,
                                                  sizeof(value) };
        m_SetWindowCompositionAttribute(m_handle, &data);
    }

    m_FlushMenuThemes();

    ::UpdateWindow(m_handle);

    m_is_dark_mode_enabled = true;
}

/////////////////////////////////////
/////////////////////////////////////
auto WinAddons::isSystemDarkModeEnabled() const noexcept -> bool {
    if (!isDarkModeSupported()) return false;

    return m_IsDarkModeAllowedForWindow(m_handle) && m_ShouldAppsUseDarkMode();
}

/////////////////////////////////////
/////////////////////////////////////
auto WinAddons::loadFunctions() -> void {
    m_RtlGetNtVersionNumbers =
        reinterpret_cast<fnRtlGetNtVersionNumbers>(m_ntdll.resolve("RtlGetNtVersionNumbers"));
    Q_ASSERT(m_RtlGetNtVersionNumbers);

    m_RtlGetNtVersionNumbers(&m_windows_version.major,
                             &m_windows_version.minor,
                             &m_windows_version.build_number);
    m_windows_version.build_number &= ~0xF0000000;

    if (m_windows_version.major != 10 ||
        (m_windows_version.minor == 0 && m_windows_version.build_number < 17763))
        return;

    if (m_windows_version.build_number < 18362) {
        m_AllowDarkModeForApp =
            reinterpret_cast<fnAllowDarkModeForApp>(m_uxtheme.resolve("AllowDarkModeForApp"));
        if (!m_AllowDarkModeForApp)
            m_AllowDarkModeForApp =
                reinterpret_cast<fnAllowDarkModeForApp>(m_uxtheme.resolve(MAKEINTRESOURCEA(135)));
    } else {
        m_SetPreferredAppMode =
            reinterpret_cast<fnSetPreferredAppMode>(m_uxtheme.resolve("SetPreferredAppMode"));
        if (!m_SetPreferredAppMode)
            m_SetPreferredAppMode =
                reinterpret_cast<fnSetPreferredAppMode>(m_uxtheme.resolve(MAKEINTRESOURCEA(135)));
    }

    m_AllowDarkModeForWindow =
        reinterpret_cast<fnAllowDarkModeForWindow>(m_uxtheme.resolve("AllowDarkModeForWindow"));
    if (!m_AllowDarkModeForWindow)
        m_AllowDarkModeForWindow =
            reinterpret_cast<fnAllowDarkModeForWindow>(m_uxtheme.resolve(MAKEINTRESOURCEA(133)));

    m_ShouldAppsUseDarkMode =
        reinterpret_cast<fnShouldAppsUseDarkMode>(m_uxtheme.resolve("ShouldAppsUseDarkMode"));
    if (!m_ShouldAppsUseDarkMode)
        m_ShouldAppsUseDarkMode =
            reinterpret_cast<fnShouldAppsUseDarkMode>(m_uxtheme.resolve(MAKEINTRESOURCEA(132)));

    m_IsDarkModeAllowedForWindow = reinterpret_cast<fnIsDarkModeAllowedForWindow>(
        m_uxtheme.resolve("IsDarkModeAllowedForWindow"));
    if (!m_IsDarkModeAllowedForWindow)
        m_IsDarkModeAllowedForWindow = reinterpret_cast<fnIsDarkModeAllowedForWindow>(
            m_uxtheme.resolve(MAKEINTRESOURCEA(137)));

    m_IsDarkModeAllowedForApp =
        reinterpret_cast<fnIsDarkModeAllowedForApp>(m_uxtheme.resolve("IsDarkModeAllowedForApp"));
    if (!m_IsDarkModeAllowedForApp)
        m_IsDarkModeAllowedForApp =
            reinterpret_cast<fnIsDarkModeAllowedForApp>(m_uxtheme.resolve(MAKEINTRESOURCEA(139)));

    if (m_windows_version.build_number <= 17763)
        m_ShouldSystemsUseDarkMode = ShouldSystemUseDarkThemePolyfill;
    else {
        m_ShouldSystemsUseDarkMode = reinterpret_cast<fnShouldSystemUseDarkMode>(
            m_uxtheme.resolve("ShouldSystemsUseDarkMode"));
        if (!m_ShouldSystemsUseDarkMode)
            m_ShouldSystemsUseDarkMode = reinterpret_cast<fnShouldSystemUseDarkMode>(
                m_uxtheme.resolve(MAKEINTRESOURCEA(138)));
    }

    m_RefreshImmersiveColorPolicyState = reinterpret_cast<fnRefreshImmersiveColorPolicyState>(
        m_uxtheme.resolve("RefreshImmersiveColorPolicyState"));
    if (!m_RefreshImmersiveColorPolicyState)
        m_RefreshImmersiveColorPolicyState = reinterpret_cast<fnRefreshImmersiveColorPolicyState>(
            m_uxtheme.resolve(MAKEINTRESOURCEA(104)));

    m_GetIsImmersiveColorUsingHighContrast =
        reinterpret_cast<fnGetIsImmersiveColorUsingHighContrast>(
            m_uxtheme.resolve("GetIsImmersiveColorUsingHighContrast"));
    if (!m_GetIsImmersiveColorUsingHighContrast)
        m_GetIsImmersiveColorUsingHighContrast =
            reinterpret_cast<fnGetIsImmersiveColorUsingHighContrast>(
                m_uxtheme.resolve(MAKEINTRESOURCEA(106)));

    m_FlushMenuThemes = reinterpret_cast<fnFlushMenuThemes>(m_uxtheme.resolve("FlushMenuThemes"));
    if (!m_FlushMenuThemes)
        m_FlushMenuThemes =
            reinterpret_cast<fnFlushMenuThemes>(m_uxtheme.resolve(MAKEINTRESOURCEA(136)));

    m_OpenNcThemeData = reinterpret_cast<fnOpenNcThemeData>(m_uxtheme.resolve("OpenNcThemeData"));
    if (!m_OpenNcThemeData)
        m_OpenNcThemeData =
            reinterpret_cast<fnOpenNcThemeData>(m_uxtheme.resolve(MAKEINTRESOURCEA(49)));

    m_SetWindowCompositionAttribute = reinterpret_cast<fnSetWindowCompositionAttribute>(
        m_user32.resolve("SetWindowCompositionAttribute"));

    m_is_dark_mode_supported = m_OpenNcThemeData && m_RefreshImmersiveColorPolicyState &&
                               m_ShouldAppsUseDarkMode && m_AllowDarkModeForWindow &&
                               (m_AllowDarkModeForApp || m_SetPreferredAppMode);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinAddons::allowDarkMode(bool allow) -> void {
    if (m_AllowDarkModeForApp) m_AllowDarkModeForApp(allow);
    else if (m_SetPreferredAppMode)
        m_SetPreferredAppMode(allow ? PreferredAppMode::AllowDark : PreferredAppMode::Default);
}
