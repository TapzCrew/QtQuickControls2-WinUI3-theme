// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include "WinUI3Style.hpp"

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtQml/QQmlInfo>
#include <QtQuickControls2/private/qquickstyle_p.h>

#include <array>

QT_BEGIN_NAMESPACE

/////////////////////////////////////
/////////////////////////////////////
constexpr auto qquickuniversal_light_color(WinUI3Style::SystemColor role) -> QRgb {
    constexpr auto colors = std::array<QRgb, 24> {
        0xFFFFFFFF, // SystemAltHighColor
        0x33FFFFFF, // SystemAltLowColor
        0x99FFFFFF, // SystemAltMediumColor
        0xCCFFFFFF, // SystemAltMediumHighColor
        0x66FFFFFF, // SystemAltMediumLowColor
        0xFF000000, // SystemBaseHighColor
        0x33000000, // SystemBaseLowColor
        0x99000000, // SystemBaseMediumColor
        0xCC000000, // SystemBaseMediumHighColor
        0x66000000, // SystemBaseMediumLowColor
        0xFF171717, // SystemChromeAltLowColor
        0xFF000000, // SystemChromeBlackHighColor
        0x33000000, // SystemChromeBlackLowColor
        0x66000000, // SystemChromeBlackMediumLowColor
        0xCC000000, // SystemChromeBlackMediumColor
        0xFFCCCCCC, // SystemChromeDisabledHighColor
        0xFF7A7A7A, // SystemChromeDisabledLowColor
        0xFFCCCCCC, // SystemChromeHighColor
        0xFFF2F2F2, // SystemChromeLowColor
        0xFFE6E6E6, // SystemChromeMediumColor
        0xFFF2F2F2, // SystemChromeMediumLowColor
        0xFFFFFFFF, // SystemChromeWhiteColor
        0x19000000, // SystemListLowColor
        0x33000000  // SystemListMediumColor
    };

    return colors[static_cast<std::size_t>(role)];
}

/////////////////////////////////////
/////////////////////////////////////
constexpr auto qquickuniversal_dark_color(WinUI3Style::SystemColor role) -> QRgb {
    constexpr auto colors = std::array<QRgb, 24> {
        0xFF000000, // SystemAltHighColor
        0x33000000, // SystemAltLowColor
        0x99000000, // SystemAltMediumColor
        0xCC000000, // SystemAltMediumHighColor
        0x66000000, // SystemAltMediumLowColor
        0xFFFFFFFF, // SystemBaseHighColor
        0x33FFFFFF, // SystemBaseLowColor
        0x99FFFFFF, // SystemBaseMediumColor
        0xCCFFFFFF, // SystemBaseMediumHighColor
        0x66FFFFFF, // SystemBaseMediumLowColor
        0xFFF2F2F2, // SystemChromeAltLowColor
        0xFF000000, // SystemChromeBlackHighColor
        0x33000000, // SystemChromeBlackLowColor
        0x66000000, // SystemChromeBlackMediumLowColor
        0xCC000000, // SystemChromeBlackMediumColor
        0xFF333333, // SystemChromeDisabledHighColor
        0xFF858585, // SystemChromeDisabledLowColor
        0xFF767676, // SystemChromeHighColor
        0xFF171717, // SystemChromeLowColor
        0xFF1F1F1F, // SystemChromeMediumColor
        0xFF2B2B2B, // SystemChromeMediumLowColor
        0xFFFFFFFF, // SystemChromeWhiteColor
        0x19FFFFFF, // SystemListLowColor
        0x33FFFFFF  // SystemListMediumColor
    };

    return colors[static_cast<std::size_t>(role)];
}

/////////////////////////////////////
/////////////////////////////////////
constexpr auto qquickuniversal_accent_color(WinUI3Style::Color accent) -> QRgb {
    constexpr auto colors = std::array<QRgb, 20> {
        0xFFA4C400, // Lime
        0xFF60A917, // Green
        0xFF008A00, // Emerald
        0xFF00ABA9, // Teal
        0xFF1BA1E2, // Cyan
        0xFF3E65FF, // Cobalt
        0xFF6A00FF, // Indigo
        0xFFAA00FF, // Violet
        0xFFF472D0, // Pink
        0xFFD80073, // Magenta
        0xFFA20025, // Crimson
        0xFFE51400, // Red
        0xFFFA6800, // Orange
        0xFFF0A30A, // Amber
        0xFFE3C800, // Yellow
        0xFF825A2C, // Brown
        0xFF6D8764, // Olive
        0xFF647687, // Steel
        0xFF76608A, // Mauve
        0xFF87794E  // Taupe
    };

    return colors[static_cast<std::size_t>(accent)];
}

/////////////////////////////////////
/////////////////////////////////////
constexpr WinUI3Style::Theme qquickuniversal_effective_theme(WinUI3Style::Theme theme) {
    if (theme == WinUI3Style::Theme::System)
        theme = QQuickStylePrivate::isDarkSystemTheme() ? WinUI3Style::Theme::Dark
                                                        : WinUI3Style::Theme::Light;

    return theme;
}

static constinit auto GLOBAL_THEME  = WinUI3Style::Theme::Light;
static constinit auto GLOBAL_ACCENT = qquickuniversal_accent_color(WinUI3Style::Color::Cobalt);
static constinit auto GLOBAL_FOREGROUND =
    qquickuniversal_light_color(WinUI3Style::SystemColor::BaseHigh);
static constinit auto GLOBAL_BACKGROUND =
    qquickuniversal_light_color(WinUI3Style::SystemColor::AltHigh);
static constinit auto HAS_GLOBAL_FOREGROUND = false;
static constinit auto HAS_GLOBAL_BACKGROUND = false;

/////////////////////////////////////
/////////////////////////////////////
WinUI3Style::WinUI3Style(QObject *parent)
    : QQuickAttachedObject { parent }, m_has_foreground { HAS_GLOBAL_FOREGROUND },
      m_has_background { HAS_GLOBAL_BACKGROUND }, m_theme { GLOBAL_THEME },
      m_accent { GLOBAL_ACCENT }, m_foreground { GLOBAL_FOREGROUND }, m_background {
          GLOBAL_BACKGROUND
      } {
    init();
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::qmlAttachedProperties(QObject *object) -> WinUI3Style * {
    return new WinUI3Style(object);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::theme() const -> WinUI3Style::Theme {
    return m_theme;
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::setTheme(Theme theme) -> void {
    theme            = qquickuniversal_effective_theme(theme);
    m_explicit_theme = true;
    if (m_theme == theme) return;

    m_theme = theme;
    propagateTheme();
    emit themeChanged();
    emit paletteChanged();
    emit foregroundChanged();
    emit backgroundChanged();
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::inheritTheme(Theme theme) -> void {
    if (m_explicit_theme || m_theme == theme) return;

    m_theme = theme;
    propagateTheme();
    emit themeChanged();
    emit paletteChanged();
    emit foregroundChanged();
    emit backgroundChanged();
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::propagateTheme() -> void {
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        WinUI3Style *universal = qobject_cast<WinUI3Style *>(child);
        if (universal) universal->inheritTheme(m_theme);
    }
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::resetTheme() -> void {
    if (!m_explicit_theme) return;

    m_explicit_theme       = false;
    WinUI3Style *universal = qobject_cast<WinUI3Style *>(attachedParent());
    inheritTheme(universal ? universal->theme() : GLOBAL_THEME);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::accent() const -> QVariant {
    return QColor::fromRgba(m_accent);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::setAccent(const QVariant &var) -> void {
    QRgb accent = 0;
    if (!variantToRgba(var, "accent", &accent)) return;

    m_explicit_accent = true;
    if (m_accent == accent) return;

    m_accent = accent;
    propagateAccent();
    emit accentChanged();
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::inheritAccent(QRgb accent) -> void {
    if (m_explicit_accent || m_accent == accent) return;

    m_accent = accent;
    propagateAccent();
    emit accentChanged();
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::propagateAccent() -> void {
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        WinUI3Style *universal = qobject_cast<WinUI3Style *>(child);
        if (universal) universal->inheritAccent(m_accent);
    }
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::resetAccent() {
    if (!m_explicit_accent) return;

    m_explicit_accent      = false;
    WinUI3Style *universal = qobject_cast<WinUI3Style *>(attachedParent());
    inheritAccent(universal ? universal->m_accent : GLOBAL_ACCENT);
}

/////////////////////////////////////
/////////////////////////////////////
QVariant WinUI3Style::foreground() const {
    if (GLOBAL_FOREGROUND) return QColor::fromRgba(m_foreground);
    return baseHighColor();
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::setForeground(const QVariant &var) {
    QRgb foreground = 0;
    if (!variantToRgba(var, "foreground", &foreground)) return;

    m_has_foreground      = true;
    m_explicit_foreground = true;
    if (m_foreground == foreground) return;

    m_foreground = foreground;
    propagateForeground();
    emit foregroundChanged();
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::inheritForeground(QRgb foreground, bool has) {
    if (m_explicit_foreground || m_foreground == foreground) return;

    m_has_foreground = has;
    m_foreground     = foreground;
    propagateForeground();
    emit foregroundChanged();
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::propagateForeground() {
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        WinUI3Style *universal = qobject_cast<WinUI3Style *>(child);
        if (universal) universal->inheritForeground(m_foreground, m_has_foreground);
    }
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::resetForeground() {
    if (!m_explicit_foreground) return;

    m_has_foreground       = false;
    m_explicit_foreground  = false;
    WinUI3Style *universal = qobject_cast<WinUI3Style *>(attachedParent());
    inheritForeground(universal ? universal->m_foreground : GLOBAL_FOREGROUND,
                      universal ? universal->m_has_foreground : false);
}

/////////////////////////////////////
/////////////////////////////////////
QVariant WinUI3Style::background() const {
    if (GLOBAL_BACKGROUND) return QColor::fromRgba(m_background);
    return altHighColor();
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::setBackground(const QVariant &var) {
    QRgb background = 0;
    if (!variantToRgba(var, "background", &background)) return;

    m_has_background      = true;
    m_explicit_background = true;
    if (m_background == background) return;

    m_background = background;
    propagateBackground();
    emit backgroundChanged();
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::inheritBackground(QRgb background, bool has) {
    if (m_explicit_background || m_background == background) return;

    m_has_background = has;
    m_background     = background;
    propagateBackground();
    emit backgroundChanged();
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::propagateBackground() {
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        WinUI3Style *universal = qobject_cast<WinUI3Style *>(child);
        if (universal) universal->inheritBackground(m_background, m_has_background);
    }
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::resetBackground() {
    if (!m_explicit_background) return;

    m_has_background       = false;
    m_explicit_background  = false;
    WinUI3Style *universal = qobject_cast<WinUI3Style *>(attachedParent());
    inheritBackground(universal ? universal->m_background : GLOBAL_BACKGROUND,
                      universal ? universal->m_has_background : false);
}

/////////////////////////////////////
/////////////////////////////////////
QColor WinUI3Style::color(Color color) const {
    return qquickuniversal_accent_color(color);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::altHighColor() const -> QColor {
    return systemColor(SystemColor::AltHigh);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::altLowColor() const -> QColor {
    return systemColor(SystemColor::AltLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::altMediumColor() const -> QColor {
    return systemColor(SystemColor::AltMedium);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::altMediumHighColor() const -> QColor {
    return systemColor(SystemColor::AltMediumHigh);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::altMediumLowColor() const -> QColor {
    return systemColor(SystemColor::AltMediumLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::baseHighColor() const -> QColor {
    return systemColor(SystemColor::BaseHigh);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::baseLowColor() const -> QColor {
    return systemColor(SystemColor::BaseLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::baseMediumColor() const -> QColor {
    return systemColor(SystemColor::BaseMedium);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::baseMediumHighColor() const -> QColor {
    return systemColor(SystemColor::BaseMediumHigh);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::baseMediumLowColor() const -> QColor {
    return systemColor(SystemColor::BaseMediumLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeAltLowColor() const -> QColor {
    return systemColor(SystemColor::ChromeAltLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeBlackHighColor() const -> QColor {
    return systemColor(SystemColor::ChromeBlackHigh);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeBlackLowColor() const -> QColor {
    return systemColor(SystemColor::ChromeBlackLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeBlackMediumLowColor() const -> QColor {
    return systemColor(SystemColor::ChromeBlackMediumLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeBlackMediumColor() const -> QColor {
    return systemColor(SystemColor::ChromeBlackMedium);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeDisabledHighColor() const -> QColor {
    return systemColor(SystemColor::ChromeDisabledHigh);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeDisabledLowColor() const -> QColor {
    return systemColor(SystemColor::ChromeDisabledLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeHighColor() const -> QColor {
    return systemColor(SystemColor::ChromeHigh);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeLowColor() const -> QColor {
    return systemColor(SystemColor::ChromeLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeMediumColor() const -> QColor {
    return systemColor(SystemColor::ChromeMedium);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeMediumLowColor() const -> QColor {
    return systemColor(SystemColor::ChromeMediumLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::chromeWhiteColor() const -> QColor {
    return systemColor(SystemColor::ChromeWhite);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::listLowColor() const -> QColor {
    return systemColor(SystemColor::ListLow);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::listMediumColor() const -> QColor {
    return systemColor(SystemColor::ListMedium);
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::systemColor(SystemColor role) const -> QColor {
    return QColor::fromRgba(m_theme == WinUI3Style::Theme::Dark
                                ? qquickuniversal_dark_color(role)
                                : qquickuniversal_light_color(role));
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::attachedParentChange(QQuickAttachedObject *new_parent,
                                       [[maybe_unused]] QQuickAttachedObject *old_parent) -> void {
    WinUI3Style *winui3 = qobject_cast<WinUI3Style *>(new_parent);
    if (winui3) {
        inheritTheme(winui3->theme());
        inheritAccent(winui3->m_accent);
        inheritForeground(winui3->m_foreground, winui3->m_has_foreground);
        inheritBackground(winui3->m_background, winui3->m_has_background);
    }
}

/////////////////////////////////////
/////////////////////////////////////
template<typename Enum>
static auto toEnumValue(const QByteArray &value, bool *ok) -> Enum {
    const auto enumeration = QMetaEnum::fromType<Enum>();
    return static_cast<Enum>(enumeration.keyToValue(value, ok));
}

/////////////////////////////////////
/////////////////////////////////////
static auto resolveSetting(const QByteArray &env,
                           const QSharedPointer<QSettings> &settings,
                           const QString &name) -> QByteArray {
    auto value = qgetenv(env);
#if QT_CONFIG(settings)
    if (value.isNull() && !settings.isNull()) value = settings->value(name).toByteArray();
#endif
    return value;
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::initGlobals() -> void {
    QSharedPointer<QSettings> settings = QQuickStylePrivate::settings(QStringLiteral("WinUI3"));

    auto ok          = false;
    auto theme_value = resolveSetting("WINUI3_THEME", settings, QStringLiteral("Theme"));
    auto theme_enum  = toEnumValue<Theme>(theme_value, &ok);

    if (ok) GLOBAL_THEME = qquickuniversal_effective_theme(theme_enum);
    else if (!theme_value.isEmpty())
        qWarning().nospace().noquote() << "WinUI3: unknown theme value: " << theme_value;

    auto accent_value = resolveSetting("WINUI3_ACCENT", settings, QStringLiteral("Accent"));
    auto accent_enum  = toEnumValue<Color>(accent_value, &ok);
    if (ok) GLOBAL_ACCENT = qquickuniversal_accent_color(accent_enum);
    else if (!accent_value.isEmpty()) {
        auto color = QColor { QString { accent_value } };
        if (color.isValid()) GLOBAL_ACCENT = color.rgba();
        else
            qWarning().nospace().noquote() << "WinUI3: unknown accent value: " << accent_value;
    }

    auto foreground_value =
        resolveSetting("WINUI3_FOREGROUND", settings, QStringLiteral("Foreground"));
    auto foreground_enum = toEnumValue<Color>(foreground_value, &ok);

    if (ok) {
        GLOBAL_FOREGROUND     = qquickuniversal_accent_color(foreground_enum);
        HAS_GLOBAL_FOREGROUND = true;
    } else if (!foreground_value.isEmpty()) {
        const auto color = QColor { QString { foreground_value } };
        if (color.isValid()) {
            GLOBAL_FOREGROUND     = color.rgba();
            HAS_GLOBAL_FOREGROUND = true;
        } else
            qWarning().nospace().noquote()
                << "WinUI3: unknown foreground value: " << foreground_value;
    }

    auto background_value =
        resolveSetting("WINUI3_BACKGROUND", settings, QStringLiteral("Background"));
    auto background_enum = toEnumValue<Color>(background_value, &ok);

    if (ok) {
        GLOBAL_BACKGROUND     = qquickuniversal_accent_color(background_enum);
        HAS_GLOBAL_BACKGROUND = true;
    } else if (!background_value.isEmpty()) {
        const auto color = QColor { QString { background_value } };

        if (color.isValid()) {
            GLOBAL_BACKGROUND     = color.rgba();
            HAS_GLOBAL_BACKGROUND = true;
        } else {
            qWarning().nospace().noquote()
                << "WinUI3: unknown background value: " << background_value;
        }
    }
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Style::variantToRgba(const QVariant &var, const char *name, QRgb *rgba) const -> bool {
    if (var.metaType().id() == QMetaType::Int) {
        const auto val = var.toInt();

        if (val < static_cast<int>(Color::Lime) || val > static_cast<int>(Color::Taupe)) {
            qmlWarning(parent()) << "unknown WinUI3." << name << " value: " << val;
            return false;
        }

        *rgba = qquickuniversal_accent_color(static_cast<Color>(val));
    } else {
        auto val = QMetaEnum::fromType<Color>().keyToValue(var.toByteArray());
        if (val != -1) *rgba = qquickuniversal_accent_color(static_cast<Color>(val));
        else {
            auto color = QColor { var.toString() };

            if (!color.isValid()) {
                qmlWarning(parent()) << "unknown WinUI3." << name << " value: " << var.toString();
                return false;
            }

            *rgba = color.rgba();
        }
    }
    return true;
}
