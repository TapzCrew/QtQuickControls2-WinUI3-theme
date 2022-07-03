// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

/////////////////////////////////////
/////////////////////////////////////
inline auto WinAddons::isDarkModeSupported() const noexcept -> bool {
    return m_is_dark_mode_supported;
}

/////////////////////////////////////
/////////////////////////////////////
inline auto WinAddons::isDarkModeEnabled() const noexcept -> bool {
    return m_is_dark_mode_enabled;
}

/////////////////////////////////////
/////////////////////////////////////
inline auto WinAddons::windowsVersion() const noexcept -> const Version & {
    return m_windows_version;
}

/////////////////////////////////////
/////////////////////////////////////
inline auto WinAddons::handle() const noexcept -> HWND {
    return m_handle;
}
