// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include "WinUI3Style.hpp"

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtQml/QQmlInfo>
#include <QtQuickControls2/private/qquickstyle_p.h>

#include <winrt/Windows.UI.ViewManagement.h>

#include <array>

static constexpr auto ACCENT_COLOR_MAP =
    std::array<winrt::Windows::UI::ViewManagement::UIColorType, 7> {
        winrt::Windows::UI::ViewManagement::UIColorType::AccentDark3,
        winrt::Windows::UI::ViewManagement::UIColorType::AccentDark2,
        winrt::Windows::UI::ViewManagement::UIColorType::AccentDark1,
        winrt::Windows::UI::ViewManagement::UIColorType::Accent,
        winrt::Windows::UI::ViewManagement::UIColorType::AccentLight1,
        winrt::Windows::UI::ViewManagement::UIColorType::AccentLight2,
        winrt::Windows::UI::ViewManagement::UIColorType::AccentLight3
    };

/////////////////////////////////////
/////////////////////////////////////
template<typename Enum>
Enum toEnumValue(const QByteArray &value, bool *ok) {
    const auto enumeration = QMetaEnum::fromType<Enum>();
    return static_cast<Enum>(enumeration.keyToValue(value, ok));
}

/////////////////////////////////////
/////////////////////////////////////
QByteArray resolveSetting(const QByteArray &env,
                          const QSharedPointer<QSettings> &settings,
                          const QString &name) {
    auto value = qgetenv(env);
#if QT_CONFIG(settings)
    if (value.isNull() && !settings.isNull()) value = settings->value(name).toByteArray();
#endif
    return value;
}

/////////////////////////////////////
/////////////////////////////////////
QColor getSystemColor(winrt::Windows::UI::ViewManagement::UIColorType win_color) {
    using namespace winrt;
    using namespace Windows::UI::ViewManagement;

    auto ui_settings = UISettings {};
    const auto color = ui_settings.GetColorValue(win_color);

    return QColor { color.R, color.G, color.B, 255 }.rgba();
}

/////////////////////////////////////
/////////////////////////////////////
constexpr QRgb qquickwinui3_light_color(WinUI3Style::SystemColor role) {
    constexpr auto colors = std::array<QRgb, 72> {
        0xE4000000, // TextFillColorPrimary
        0x9E000000, // TextFillColorSecondary
        0x72000000, // TextFillColorTertiary
        0x5C000000, // TextFillColorDisabled
        0xFFFFFFFF, // TextFillColorInverse

        0x5C000000, // AccentTextFillColorDisabled

        0xFFFFFFFF, // TextOnAccentFillColorSelectedText
        0xFFFFFFFF, // TextOnAccentFillColorPrimary
        0xB3FFFFFF, // TextOnAccentFillColorSecondary
        0xFFFFFFFF, // TextOnAccentFillColorDisabled

        0xB3FFFFFF, // ControlFillColorDefault
        0x80F9F9F9, // ControlFillColorSecondary
        0x4DF9F9F9, // ControlFillColorTertiary
        0x4DF9F9F9, // ControlFillColorDisabled
        0x00FFFFFF, // ControlFillColorTransparent
        0xFFFFFFFF, // ControlFillColorInputActive

        0x72000000, // ControlStrongFillColorDefault
        0x51000000, // ControlStrongFillColorDisabled

        0xFFFFFFFF, // ControlSolidFillColorDefault

        0x00FFFFFF, // SubtleFillColorTransparent
        0x09000000, // SubtleFillColorSecondary
        0x06000000, // SubtleFillColorTertiary
        0x00FFFFFF, // SubtleFillColorDisabled

        0x00FFFFFF, // ControlAltFillColorTransparent
        0x06000000, // ControlAltFillColorSecondary
        0x0F000000, // ControlAltFillColorTertiary
        0x18000000, // ControlAltFillColorQuarternary
        0x00FFFFFF, // ControlAltFillColorDisabled

        0xC9FFFFFF, // ControlOnImageFillColorDefault
        0xFFF3F3F3, // ControlOnImageFillColorSecondary
        0xFFEBEBEB, // ControlOnImageFillColorTertiary
        0x00FFFFFF, // ControlOnImageFillColorDisabled

        0x37000000, // AccentFillColorDisabled

        0x0F000000, // ControlStrokeColorDefault
        0x29000000, // ControlStrokeColorSecondary

        0x14FFFFFF, // ControlStrokeColorOnAccentDefault
        0x66000000, // ControlStrokeColorOnAccentSecondary
        0x37000000, // ControlStrokeColorOnAccentTertiary
        0x0F000000, // ControlStrokeColorOnAccentDisabled

        0x59FFFFFF, // ControlStrokeColorForStrongFillWhenOnImage

        0x0F000000, // CardStrokeColorDefault
        0xFFEBEBEB, // CardStrokeColorDefaultSolid

        0x72000000, // ControlStrongStrokeColorDefault
        0x37000000, // ControlStrongStrokeColorDisabled

        0x66757575, // SurfaceStrokeColorDefault
        0x0F000000, // SurfaceStrokeColorFlyout
        0x15FFFFFF, // SurfaceStrokeColorInverse

        0x0F000000, // DividerStrokeColorDefault

        0xE4000000, // FocusStrokeColorOuter
        0xB3FFFFFF, // FocusStrokeColorInner

        0xB3FFFFFF, // CardBackgroundFillColorDefault
        0x80F6F6F6, // CardBackgroundFillColorSecondary

        0x4D000000, // SmokeFillColorDefault

        0x80FFFFFF, // LayerFillColorDefault
        0xFFFFFFFF, // LayerFillColorAlt

        0x40FFFFFF, // LayerOnAcrylicFillColorDefault
        0x40FFFFFF, // LayerOnAccentAcrylicFillColorDefault

        0xFFEEEEEE, // SolidBackgroundFillColorSecondary
        0xFFF9F9F9, // SolidBackgroundFillColorTertiary
        0xFFFFFFFF, // SolidBackgroundFillColorQuarternary

        0xFF0F7B0F, // SystemFillColorSuccess
        0xFF9D5D00, // SystemFillColorCaution
        0xFFC42B1C, // SystemFillColorCritical
        0x72000000, // SystemFillColorNeutral
        0xFF8A8A8A, // SystemFillColorSolidNeutral
        0x80F6F6F6, // SystemFillColorAttentionBackground
        0xFFDFF6DD, // SystemFillColorSuccessBackground
        0xFFFFF4CE, // SystemFillColorCautionBackground
        0xFFFDE7E9, // SystemFillColorCriticalBackground
        0x06000000, // SystemFillColorNeutralBackground
        0xFFF7F7F7, // SystemFillColorSolidAttentionBackground
        0xFFF3F3F3, // SystemFillColorSolidNeutralBackground
    };

    return colors[static_cast<std::size_t>(role)];
}

/////////////////////////////////////
/////////////////////////////////////
constexpr QRgb qquickwinui3_dark_color(WinUI3Style::SystemColor role) {
    constexpr auto colors = std::array<QRgb, 72> {
        0xDDFFFFFF, // TextFillColorPrimary
        0xC5FFFFFF, // TextFillColorSecondary
        0x87FFFFFF, // TextFillColorTertiary
        0x5DFFFFFF, // TextFillColorDisabled
        0xE4000000, // TextFillColorInverse

        0x5DFFFFFF, // AccentTextFillColorDisabled

        0xDDFFFFFF, // TextOnAccentFillColorSelectedText
        0xDD000000, // TextOnAccentFillColorPrimary
        0x80000000, // TextOnAccentFillColorSecondary
        0x87FFFFFF, // TextOnAccentFillColorDisabled

        0x0FFFFFFF, // ControlFillColorDefault
        0x15FFFFFF, // ControlFillColorSecondary
        0x08FFFFFF, // ControlFillColorTertiary
        0x0BFFFFFF, // ControlFillColorDisabled
        0x00FFFFFF, // ControlFillColorTransparent
        0xB31E1E1E, // ControlFillColorInputActive

        0x8BFFFFFF, // ControlStrongFillColorDefault
        0x3FFFFFFF, // ControlStrongFillColorDisabled

        0xDD454545, // ControlSolidFillColorDefault

        0x00FFFFFF, // SubtleFillColorTransparent
        0x0FFFFFFF, // SubtleFillColorSecondary
        0x0AFFFFFF, // SubtleFillColorTertiary
        0x00FFFFFF, // SubtleFillColorDisabled

        0x00FFFFFF, // ControlAltFillColorTransparent
        0x19000000, // ControlAltFillColorSecondary
        0x0BFFFFFF, // ControlAltFillColorTertiary
        0x12FFFFFF, // ControlAltFillColorQuarternary
        0x00FFFFFF, // ControlAltFillColorDisabled

        0xB31C1C1C, // ControlOnImageFillColorDefault
        0xFF1A1A1A, // ControlOnImageFillColorSecondary
        0xFF131313, // ControlOnImageFillColorTertiary
        0xFF1E1E1E, // ControlOnImageFillColorDisabled

        0x28FFFFFF, // AccentFillColorDisabled

        0x12FFFFFF, // ControlStrokeColorDefault
        0x18FFFFFF, // ControlStrokeColorSecondary
        0x14FFFFFF, // ControlStrokeColorOnAccentDefault
        0x23000000, // ControlStrokeColorOnAccentSecondary
        0x37000000, // ControlStrokeColorOnAccentTertiary
        0x33000000, // ControlStrokeColorOnAccentDisabled
        0x6B000000, // ControlStrokeColorForStrongFillWhenOnImage

        0x19000000, // CardStrokeColorDefault
        0xFF1C1C1C, // CardStrokeColorDefaultSolid

        0x8BFFFFFF, // ControlStrongStrokeColorDefault
        0x28FFFFFF, // ControlStrongStrokeColorDisabled

        0x66757575, // SurfaceStrokeColorDefault
        0x33000000, // SurfaceStrokeColorFlyout
        0x0F000000, // SurfaceStrokeColorInverse

        0x15FFFFFF, // DividerStrokeColorDefault

        0xFFFFFFFF, // FocusStrokeColorOuter
        0xB3000000, // FocusStrokeColorInner

        0x0DFFFFFF, // CardBackgroundFillColorDefault
        0x08FFFFFF, // CardBackgroundFillColorSecondary

        0x4D000000, // SmokeFillColorDefault

        0x4C3A3A3A, // LayerFillColorDefault
        0x0DFFFFFF, // LayerFillColorAlt

        0x09FFFFFF, // LayerOnAcrylicFillColorDefault
        0x09FFFFFF, // LayerOnAccentAcrylicFillColorDefault

        0xFF1C1C1C, // SolidBackgroundFillColorSecondary
        0xFF282828, // SolidBackgroundFillColorTertiary
        0xFF2C2C2C, // SolidBackgroundFillColorQuarternary

        0xFF6CCB5F, // SystemFillColorSuccess
        0xFFFCE100, // SystemFillColorCaution
        0xFFFF99A4, // SystemFillColorCritical
        0x8BFFFFFF, // SystemFillColorNeutral
        0xFF9D9D9D, // SystemFillColorSolidNeutral
        0x08FFFFFF, // SystemFillColorAttentionBackground
        0xFF393D1B, // SystemFillColorSuccessBackground
        0xFF433519, // SystemFillColorCautionBackground
        0xFF442726, // SystemFillColorCriticalBackground
        0x08FFFFFF, // SystemFillColorNeutralBackground
        0xFF2E2E2E, // SystemFillColorSolidAttentionBackground
        0xFF2E2E2E, // SystemFillColorSolidNeutralBackground
    };

    return colors[static_cast<std::size_t>(role)];
}

/////////////////////////////////////
/////////////////////////////////////
constexpr QRgb qquickwinui3_accent_color(WinUI3Style::Color accent) {
    constexpr auto colors = std::array<QRgb, 48> {
        0xFFFFB900, // Yellow Gold,
        0xFFFF8C00, // Gold,
        0xFFF7630C, // Orange Bright,
        0xFFCA5010, // Orange Dark,
        0xFFDA3B01, // Rust,
        0xFFEF6950, // Pale Rust,
        0xFFD13438, // Brick Red,
        0xFFFF4343, // Mod Red,

        0xFFE74856, // Pale Red,
        0xFFE81123, // Red,
        0xFFEA005E, // Rose Bright,
        0xFFC30052, // Rose,
        0xFFE3008C, // Plum Light,
        0xFFBF0077, // Plum,
        0xFFC239B3, // Orchid Light,
        0xFF9A0089, // Orchid,

        0xFF0078D7, // Default Blue,
        0xFF0063B1, // Navy Blue,
        0xFF8E8CD8, // Purple Shadow,
        0xFF6B69D6, // Purple Shadow Dark,
        0xFF8764B8, // Iris Pastel,
        0xFF744DA9, // Iris Spring,
        0xFFB146C2, // Violet Red Light,
        0xFF881798, // Violet Red,

        0xFF0099BC, // Cool Blue Bright,
        0xFF2D7D9A, // Cool Blue,
        0xFF00B7C3, // Seafoam,
        0xFF038387, // Seafoam Team,
        0xFF00B294, // Mint Light,
        0xFF018574, // Mint Dark,
        0xFF00CC6A, // Turf Green,
        0xFF10893E, // Sport Green,

        0xFF7A7574, // Gray,
        0xFF5D5A58, // Gray Brown,
        0xFF68768A, // Steel Blue,
        0xFF515C6B, // Metal Blue,
        0xFF567C73, // Pale Moss,
        0xFF486860, // Moss,
        0xFF498205, // Meadow Green,
        0xFF107C10, // Green,

        0xFF767676, // Overcast,
        0xFF4C4A48, // Storm,
        0xFF69797E, // Blue Gray,
        0xFF4A5459, // Gray Dark,
        0xFF647C64, // Liddy Green,
        0xFF525E54, // Sage,
        0xFF847545, // Camouflage Desert,
        0xFF7E735F, // Camouflage,
    };

    return colors[static_cast<std::size_t>(accent)];
}

/////////////////////////////////////
/////////////////////////////////////
WinUI3Style::Theme qquickwinui3_effective_theme(WinUI3Style::Theme theme) {
    if (theme == WinUI3Style::Theme::System)
        theme = QQuickStylePrivate::isDarkSystemTheme() ? WinUI3Style::Theme::Dark
                                                        : WinUI3Style::Theme::Light;

    return theme;
}

static constinit auto GLOBAL_THEME  = WinUI3Style::Theme::Light;
static constinit auto GLOBAL_ACCENT = qquickwinui3_accent_color(WinUI3Style::Color::DefaultBlue);

/////////////////////////////////////
/////////////////////////////////////
WinUI3Style::WinUI3Style(QObject *parent)
    : QQuickAttachedObject { parent }, m_theme { GLOBAL_THEME }, m_accent { GLOBAL_ACCENT } {
    init();
}

/////////////////////////////////////
/////////////////////////////////////
WinUI3Style::~WinUI3Style() = default;

/////////////////////////////////////
/////////////////////////////////////
WinUI3Style *WinUI3Style::qmlAttachedProperties(QObject *object) {
    return new WinUI3Style { object };
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::setTheme(Theme theme) {
    theme            = qquickwinui3_effective_theme(theme);
    m_explicit_theme = true;

    if (m_theme == theme) return;

    m_theme = theme;
    propagateTheme();

    emit themeChanged(m_theme);
    emit paletteChanged();
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::inheritTheme(Theme theme) {
    if (m_explicit_theme || m_theme == theme) return;

    m_theme = theme;
    propagateTheme();

    emit themeChanged(m_theme);
    emit paletteChanged();
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::propagateTheme() {
    const auto styles = attachedChildren();

    for (auto child : styles) {
        auto winui3 = qobject_cast<WinUI3Style *>(child);
        if (winui3) winui3->inheritTheme(m_theme);
    }
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::resetTheme() {
    if (!m_explicit_theme) return;

    m_explicit_theme = false;
    auto winui3      = qobject_cast<WinUI3Style *>(attachedParent());
    inheritTheme(winui3 ? winui3->theme() : GLOBAL_THEME);
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::setAccent(const QVariant &var) {
    QRgb accent = 0;
    if (!variantToRgba(var, "accent", &accent)) return;

    m_explicit_accent = true;
    if (m_accent == accent) return;

    m_accent = accent;
    propagateAccent();

    emit accentChanged(m_accent);
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::inheritAccent(QRgb accent) {
    if (m_explicit_accent || m_accent == accent) return;

    m_accent = accent;
    propagateAccent();

    emit accentChanged(m_accent);
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::propagateAccent() {
    const auto styles = attachedChildren();
    for (auto child : styles) {
        auto winui3 = qobject_cast<WinUI3Style *>(child);
        if (winui3) winui3->inheritAccent(m_accent);
    }
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::resetAccent() {
    if (!m_explicit_accent) return;

    m_explicit_accent = false;
    auto winui3       = qobject_cast<WinUI3Style *>(attachedParent());
    inheritAccent(winui3 ? winui3->m_accent : GLOBAL_ACCENT);
}

/////////////////////////////////////
/////////////////////////////////////
QColor WinUI3Style::color(Color color) const {
    if (const auto c = static_cast<int>(color);
        c >= static_cast<int>(Color::AccentDark3) && c <= static_cast<int>(Color::AccentLight3))
        return getSystemColor(ACCENT_COLOR_MAP[c - static_cast<int>(Color::AccentDark3)]);

    return qquickwinui3_accent_color(color);
}
/////////////////////////////////////
/////////////////////////////////////
QColor WinUI3Style::systemColor(SystemColor role) const {
    return QColor::fromRgba(m_theme == WinUI3Style::Theme::Dark ? qquickwinui3_dark_color(role)
                                                                : qquickwinui3_light_color(role));
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::attachedParentChange(QQuickAttachedObject *new_parent,
                                       [[maybe_unused]] QQuickAttachedObject *old_parent) {
    auto winui3 = qobject_cast<WinUI3Style *>(new_parent);
    if (winui3) {
        inheritTheme(winui3->theme());
        inheritAccent(winui3->m_accent);
    }
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Style::initGlobals() {
    auto settings = QQuickStylePrivate::settings(QStringLiteral("WinUI3Style"));

    auto ok                = false;
    const auto theme_value = resolveSetting("WINUI3_THEME", settings, QStringLiteral("Theme"));
    const auto theme_enum  = toEnumValue<Theme>(theme_value, &ok);

    if (ok) GLOBAL_THEME = qquickwinui3_effective_theme(theme_enum);
    else if (!theme_value.isEmpty())
        qWarning().nospace().noquote() << "WinUI3: unknown theme value: " << theme_value;

    const auto accent_value = resolveSetting("WINUI3_ACCENT", settings, QStringLiteral("Accent"));
    const auto accent_enum  = toEnumValue<Color>(accent_value, &ok);
    if (ok) GLOBAL_ACCENT = qquickwinui3_accent_color(accent_enum);
    else if (!accent_value.isEmpty()) {
        auto color = QColor { QString { accent_value } };
        if (color.isValid()) GLOBAL_ACCENT = color.rgba();
        else
            qWarning().nospace().noquote() << "WinUI3: unknown accent value: " << accent_value;
    }
}

/////////////////////////////////////
/////////////////////////////////////
bool WinUI3Style::variantToRgba(const QVariant &var, const char *name, QRgb *rgba) const {
    if (var.metaType().id() == QMetaType::Int) {
        const auto val = var.toInt();

        if (val < static_cast<int>(Color::YellowGold) ||
            val > static_cast<int>(Color::Camouflage)) {
            qmlWarning(parent()) << "unknown WinUI3." << name << " value: " << val;
            return false;
        }

        *rgba = qquickwinui3_accent_color(static_cast<Color>(val));
    } else {
        const auto val = QMetaEnum::fromType<Color>().keyToValue(var.toByteArray());

        if (val != -1) *rgba = qquickwinui3_accent_color(static_cast<Color>(val));
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
