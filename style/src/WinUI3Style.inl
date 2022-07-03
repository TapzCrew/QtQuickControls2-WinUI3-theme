// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

/////////////////////////////////////
/////////////////////////////////////
inline WinUI3Style::Theme WinUI3Style::theme() const noexcept {
    return m_theme;
}

/////////////////////////////////////
/////////////////////////////////////
inline QVariant WinUI3Style::accent() const noexcept {
    return QColor::fromRgba(m_accent);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::textFillColorPrimary() const noexcept {
    return systemColor(SystemColor::TextFillColorPrimary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::textFillColorSecondary() const noexcept {
    return systemColor(SystemColor::TextFillColorSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::textFillColorTertiary() const noexcept {
    return systemColor(SystemColor::TextFillColorTertiary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::textFillColorDisabled() const noexcept {
    return systemColor(SystemColor::TextFillColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::textFillColorInverse() const noexcept {
    return systemColor(SystemColor::TextFillColorInverse);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::accentTextFillColorDisabled() const noexcept {
    return systemColor(SystemColor::AccentTextFillColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::textOnAccentFillColorSelectedText() const noexcept {
    return systemColor(SystemColor::TextOnAccentFillColorSelectedText);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::textOnAccentFillColorPrimary() const noexcept {
    return systemColor(SystemColor::TextOnAccentFillColorPrimary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::textOnAccentFillColorSecondary() const noexcept {
    return systemColor(SystemColor::TextOnAccentFillColorSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::textOnAccentFillColorDisabled() const noexcept {
    return systemColor(SystemColor::TextOnAccentFillColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlFillColorDefault() const noexcept {
    return systemColor(SystemColor::ControlFillColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlFillColorSecondary() const noexcept {
    return systemColor(SystemColor::ControlFillColorSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlFillColorTertiary() const noexcept {
    return systemColor(SystemColor::ControlFillColorTertiary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlFillColorDisabled() const noexcept {
    return systemColor(SystemColor::ControlFillColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlFillColorTransparent() const noexcept {
    return systemColor(SystemColor::ControlFillColorTransparent);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlFillColorInputActive() const noexcept {
    return systemColor(SystemColor::ControlFillColorInputActive);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrongFillColorDefault() const noexcept {
    return systemColor(SystemColor::ControlStrongFillColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrongFillColorDisabled() const noexcept {
    return systemColor(SystemColor::ControlStrongFillColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlSolidFillColorDefault() const noexcept {
    return systemColor(SystemColor::ControlSolidFillColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::subtleFillColorTransparent() const noexcept {
    return systemColor(SystemColor::SubtleFillColorTransparent);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::subtleFillColorSecondary() const noexcept {
    return systemColor(SystemColor::SubtleFillColorSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::subtleFillColorTertiary() const noexcept {
    return systemColor(SystemColor::SubtleFillColorTertiary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::subtleFillColorDisabled() const noexcept {
    return systemColor(SystemColor::SubtleFillColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlAltFillColorTransparent() const noexcept {
    return systemColor(SystemColor::ControlAltFillColorTransparent);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlAltFillColorSecondary() const noexcept {
    return systemColor(SystemColor::ControlAltFillColorSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlAltFillColorTertiary() const noexcept {
    return systemColor(SystemColor::ControlAltFillColorTertiary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlAltFillColorQuarternary() const noexcept {
    return systemColor(SystemColor::ControlAltFillColorQuarternary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlAltFillColorDisabled() const noexcept {
    return systemColor(SystemColor::ControlAltFillColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlOnImageFillColorDefault() const noexcept {
    return systemColor(SystemColor::ControlOnImageFillColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlOnImageFillColorSecondary() const noexcept {
    return systemColor(SystemColor::ControlOnImageFillColorSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlOnImageFillColorTertiary() const noexcept {
    return systemColor(SystemColor::ControlOnImageFillColorTertiary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlOnImageFillColorDisabled() const noexcept {
    return systemColor(SystemColor::ControlOnImageFillColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::accentFillColorPrimary() const noexcept {
    return color((m_theme == Theme::Dark) ? Color::AccentLight2 : Color::AccentDark1);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::accentFillColorSecondary() const noexcept {
    auto color = accentFillColorPrimary();
    color.setAlphaF(0.9);

    return color;
}
/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::accentFillColorTertiary() const noexcept {
    auto color = accentFillColorPrimary();
    color.setAlphaF(0.8);

    return color;
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::accentFillColorDisabled() const noexcept {
    return systemColor(SystemColor::AccentFillColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrokeColorDefault() const noexcept {
    return systemColor(SystemColor::ControlStrokeColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrokeColorSecondary() const noexcept {
    return systemColor(SystemColor::ControlStrokeColorSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrokeColorOnAccentDefault() const noexcept {
    return systemColor(SystemColor::ControlStrokeColorOnAccentDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrokeColorOnAccentSecondary() const noexcept {
    return systemColor(SystemColor::ControlStrokeColorOnAccentSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrokeColorOnAccentTertiary() const noexcept {
    return systemColor(SystemColor::ControlStrokeColorOnAccentTertiary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrokeColorOnAccentDisabled() const noexcept {
    return systemColor(SystemColor::ControlStrokeColorOnAccentDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrokeColorForStrongFillWhenOnImage() const noexcept {
    return systemColor(SystemColor::ControlStrokeColorForStrongFillWhenOnImage);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::cardStrokeColorDefault() const noexcept {
    return systemColor(SystemColor::CardStrokeColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::cardStrokeColorDefaultSolid() const noexcept {
    return systemColor(SystemColor::CardStrokeColorDefaultSolid);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrongStrokeColorDefault() const noexcept {
    return systemColor(SystemColor::ControlStrongStrokeColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::controlStrongStrokeColorDisabled() const noexcept {
    return systemColor(SystemColor::ControlStrongStrokeColorDisabled);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::surfaceStrokeColorDefault() const noexcept {
    return systemColor(SystemColor::SurfaceStrokeColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::surfaceStrokeColorFlyOut() const noexcept {
    return systemColor(SystemColor::SurfaceStrokeColorFlyOut);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::surfaceStrokeColorInverse() const noexcept {
    return systemColor(SystemColor::SurfaceStrokeColorInverse);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::dividerStrokeColorDefault() const noexcept {
    return systemColor(SystemColor::DividerStrokeColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::focusStrokeColorOuter() const noexcept {
    return systemColor(SystemColor::FocusStrokeColorOuter);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::focusStrokeColorInner() const noexcept {
    return systemColor(SystemColor::FocusStrokeColorInner);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::cardBackgroundFillColorDefault() const noexcept {
    return systemColor(SystemColor::CardBackgroundFillColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::cardBackgroundFillColorSecondary() const noexcept {
    return systemColor(SystemColor::CardBackgroundFillColorSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::smokeFillColorDefault() const noexcept {
    return systemColor(SystemColor::SmokeFillColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::layerFillColorDefault() const noexcept {
    return systemColor(SystemColor::LayerFillColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::layerFillColorAlt() const noexcept {
    return systemColor(SystemColor::LayerFillColorAlt);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::layerOnAcrylicFillColorDefault() const noexcept {
    return systemColor(SystemColor::LayerOnAcrylicFillColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::layerOnAccentAcrylicFillColorDefault() const noexcept {
    return systemColor(SystemColor::LayerOnAccentAcrylicFillColorDefault);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::solidBackgroundFillColorSecondary() const noexcept {
    return systemColor(SystemColor::SolidBackgroundFillColorSecondary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::solidBackgroundFillColorTertiary() const noexcept {
    return systemColor(SystemColor::SolidBackgroundFillColorTertiary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::solidBackgroundFillColorQuarternary() const noexcept {
    return systemColor(SystemColor::SolidBackgroundFillColorQuarternary);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorSuccess() const noexcept {
    return systemColor(SystemColor::SystemFillColorSuccess);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorCaution() const noexcept {
    return systemColor(SystemColor::SystemFillColorCaution);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorCritical() const noexcept {
    return systemColor(SystemColor::SystemFillColorCritical);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorNeutral() const noexcept {
    return systemColor(SystemColor::SystemFillColorNeutral);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorSolidNeutral() const noexcept {
    return systemColor(SystemColor::SystemFillColorSolidNeutral);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorAttentionBackground() const noexcept {
    return systemColor(SystemColor::SystemFillColorAttentionBackground);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorSuccessBackground() const noexcept {
    return systemColor(SystemColor::SystemFillColorSuccessBackground);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorCautionBackground() const noexcept {
    return systemColor(SystemColor::SystemFillColorCautionBackground);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorCriticalBackground() const noexcept {
    return systemColor(SystemColor::SystemFillColorCriticalBackground);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorNeutralBackground() const noexcept {
    return systemColor(SystemColor::SystemFillColorNeutralBackground);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorSolidAttentionBackground() const noexcept {
    return systemColor(SystemColor::SystemFillColorSolidAttentionBackground);
}

/////////////////////////////////////
/////////////////////////////////////
inline QColor WinUI3Style::systemFillColorSolidNeutralBackground() const noexcept {
    return systemColor(SystemColor::SystemFillColorSolidNeutralBackground);
}

/////////////////////////////////////
/////////////////////////////////////
inline QString WinUI3Style::iconFont() const noexcept {
    return QStringLiteral("Segoe Fluent Icons");
}
