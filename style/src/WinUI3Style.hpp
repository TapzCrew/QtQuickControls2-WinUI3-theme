// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#pragma once

#include <QtGui/QColor>
#include <QtQuickControls2Impl/private/qquickattachedobject_p.h>

class WinUI3Style: public QQuickAttachedObject {
    Q_OBJECT

    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged FINAL)
    Q_PROPERTY(
        QVariant accent READ accent WRITE setAccent RESET resetAccent NOTIFY accentChanged FINAL)

    Q_PROPERTY(QColor textFillColorPrimary READ textFillColorPrimary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor textFillColorSecondary READ textFillColorSecondary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor textFillColorTertiary READ textFillColorTertiary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor textFillColorDisabled READ textFillColorDisabled NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor textFillColorInverse READ textFillColorInverse NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor accentTextFillColorDisabled READ accentTextFillColorDisabled NOTIFY
                   paletteChanged FINAL)

    Q_PROPERTY(QColor textOnAccentFillColorSelectedText READ textOnAccentFillColorSelectedText
                   NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor textOnAccentFillColorPrimary READ textOnAccentFillColorPrimary NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor textOnAccentFillColorSecondary READ textOnAccentFillColorSecondary NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor textOnAccentFillColorDisabled READ textOnAccentFillColorDisabled NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(
        QColor controlFillColorDefault READ controlFillColorDefault NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor controlFillColorSecondary READ controlFillColorSecondary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor controlFillColorTertiary READ controlFillColorTertiary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor controlFillColorDisabled READ controlFillColorDisabled NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor controlFillColorTransparent READ controlFillColorTransparent NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor controlFillColorInputActive READ controlFillColorInputActive NOTIFY
                   paletteChanged FINAL)

    Q_PROPERTY(QColor controlStrongFillColorDefault READ controlStrongFillColorDefault NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor controlStrongFillColorDisabled READ controlStrongFillColorDisabled NOTIFY
                   paletteChanged FINAL)

    Q_PROPERTY(QColor controlSolidFillColorDefault READ controlSolidFillColorDefault NOTIFY
                   paletteChanged FINAL)

    Q_PROPERTY(QColor subtleFillColorTransparent READ subtleFillColorTransparent NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(
        QColor subtleFillColorSecondary READ subtleFillColorSecondary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor subtleFillColorTertiary READ subtleFillColorTertiary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor subtleFillColorDisabled READ subtleFillColorDisabled NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor controlOnImageFillColorDefault READ controlOnImageFillColorDefault NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor controlOnImageFillColorSecondary READ controlOnImageFillColorSecondary NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor controlOnImageFillColorTertiary READ controlOnImageFillColorTertiary NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor controlOnImageFillColorDisabled READ controlOnImageFillColorDisabled NOTIFY
                   paletteChanged FINAL)

    Q_PROPERTY(
        QColor accentFillColorPrimary READ accentFillColorPrimary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor accentFillColorSecondary READ accentFillColorSecondary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor accentFillColorTertiary READ accentFillColorTertiary NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor accentFillColorDisabled READ accentFillColorDisabled NOTIFY paletteChanged FINAL)

    Q_PROPERTY(
        QColor controlStrokeColorDefault READ controlStrokeColorDefault NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor controlStrokeColorSecondary READ controlStrokeColorSecondary NOTIFY
                   paletteChanged FINAL)

    Q_PROPERTY(QColor controlStrokeColorOnAccentDefault READ controlStrokeColorOnAccentDefault
                   NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor controlStrokeColorOnAccentSecondary READ controlStrokeColorOnAccentSecondary
                   NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor controlStrokeColorOnAccentTertiary READ controlStrokeColorOnAccentTertiary
                   NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor controlStrokeColorOnAccentDisabled READ controlStrokeColorOnAccentDisabled
                   NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor controlStrokeColorForStrongFillWhenOnImage READ
                   controlStrokeColorForStrongFillWhenOnImage NOTIFY paletteChanged FINAL)

    Q_PROPERTY(
        QColor cardStrokeColorDefault READ cardStrokeColorDefault NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor cardStrokeColorDefaultSolid READ cardStrokeColorDefaultSolid NOTIFY
                   paletteChanged FINAL)

    Q_PROPERTY(QColor controlStrongStrokeColorDefault READ controlStrongStrokeColorDefault NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor controlStrongStrokeColorDisabled READ controlStrongStrokeColorDisabled NOTIFY
                   paletteChanged FINAL)

    Q_PROPERTY(
        QColor surfaceStrokeColorDefault READ surfaceStrokeColorDefault NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor surfaceStrokeColorFlyOut READ surfaceStrokeColorFlyOut NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor surfaceStrokeColorInverse READ surfaceStrokeColorInverse NOTIFY paletteChanged FINAL)

    Q_PROPERTY(
        QColor dividerStrokeColorDefault READ dividerStrokeColorDefault NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor focusStrokeColorOuter READ focusStrokeColorOuter NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor focusStrokeColorInner READ focusStrokeColorInner NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor cardBackgroundFillColorDefault READ cardBackgroundFillColorDefault NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor cardBackgroundFillColorSecondary READ cardBackgroundFillColorSecondary NOTIFY
                   paletteChanged FINAL)

    Q_PROPERTY(QColor smokeFillColorDefault READ smokeFillColorDefault NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor layerFillColorDefault READ layerFillColorDefault NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor layerFillColorAlt READ layerFillColorAlt NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor layerOnAcrylicFillColorDefault READ layerOnAcrylicFillColorDefault NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor layerOnAccentAcrylicFillColorDefault READ layerOnAccentAcrylicFillColorDefault
                   NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor solidBackgroundFillColorSecondary READ solidBackgroundFillColorSecondary
                   NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor solidBackgroundFillColorTertiary READ solidBackgroundFillColorTertiary NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor solidBackgroundFillColorQuarternary READ solidBackgroundFillColorQuarternary
                   NOTIFY paletteChanged FINAL)

    Q_PROPERTY(
        QColor systemFillColorSuccess READ systemFillColorSuccess NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor systemFillColorCaution READ systemFillColorCaution NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor systemFillColorCritical READ systemFillColorCritical NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor systemFillColorNeutral READ systemFillColorNeutral NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor systemFillColorSolidNeutral READ systemFillColorSolidNeutral NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor systemFillColorAttentionBackground READ systemFillColorAttentionBackground
                   NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor systemFillColorSuccessBackground READ systemFillColorSuccessBackground NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor systemFillColorCautionBackground READ systemFillColorCautionBackground NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor systemFillColorCriticalBackground READ systemFillColorCriticalBackground
                   NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor systemFillColorNeutralBackground READ systemFillColorNeutralBackground NOTIFY
                   paletteChanged FINAL)
    Q_PROPERTY(QColor systemFillColorSolidAttentionBackground READ
                   systemFillColorSolidAttentionBackground NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor systemFillColorSolidNeutralBackground READ
                   systemFillColorSolidNeutralBackground NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QString iconFont READ iconFont NOTIFY iconFontChanged FINAL)

    QML_NAMED_ELEMENT(WinUI3Style)
    QML_ATTACHED(WinUI3Style)
    QML_UNCREATABLE("")

  public:
    enum class Color {
        YellowGold,
        Gold,
        OrangeBright,
        OrangeDark,
        Rust,
        PaleRust,
        BrickRed,
        ModRed,

        PaleRed,
        Red,
        RoseBright,
        Rose,
        PlumLight,
        Plum,
        OrchidLight,
        Orchid,

        DefaultBlue,
        NavyBlue,
        PurpleShadow,
        PurpleShadowDark,
        IrisPastel,
        IrisSpring,
        VioletRedLight,
        VioletRed,

        CoolBlueBright,
        CoolBlue,
        Seafoam,
        SeafoamTeam,
        MintLight,
        MintDark,
        TurfGreen,
        SportGreen,

        Gray,
        GrayBrown,
        SteelBlue,
        MetalBlue,
        PaleMoss,
        Moss,
        MeadowGreen,
        Green,

        Overcast,
        Storm,
        BlueGray,
        GrayDark,
        LiddyGreen,
        Sage,
        CamouflageDesert,
        Camouflage,

        AccentDark3,
        AccentDark2,
        AccentDark1,
        Accent,
        AccentLight1,
        AccentLight2,
        AccentLight3,
    };
    Q_ENUM(Color)

    enum class Theme { Light, Dark, System };
    Q_ENUM(Theme)

    enum class SystemColor {
        TextFillColorPrimary,
        TextFillColorSecondary,
        TextFillColorTertiary,
        TextFillColorDisabled,
        TextFillColorInverse,

        AccentTextFillColorDisabled,

        TextOnAccentFillColorSelectedText,
        TextOnAccentFillColorPrimary,
        TextOnAccentFillColorSecondary,
        TextOnAccentFillColorDisabled,

        ControlFillColorDefault,
        ControlFillColorSecondary,
        ControlFillColorTertiary,
        ControlFillColorDisabled,
        ControlFillColorTransparent,
        ControlFillColorInputActive,

        ControlStrongFillColorDefault,
        ControlStrongFillColorDisabled,

        ControlSolidFillColorDefault,

        SubtleFillColorTransparent,
        SubtleFillColorSecondary,
        SubtleFillColorTertiary,
        SubtleFillColorDisabled,

        ControlAltFillColorTransparent,
        ControlAltFillColorSecondary,
        ControlAltFillColorTertiary,
        ControlAltFillColorQuarternary,
        ControlAltFillColorDisabled,

        ControlOnImageFillColorDefault,
        ControlOnImageFillColorSecondary,
        ControlOnImageFillColorTertiary,
        ControlOnImageFillColorDisabled,

        AccentFillColorDisabled,

        ControlStrokeColorDefault,
        ControlStrokeColorSecondary,

        ControlStrokeColorOnAccentDefault,
        ControlStrokeColorOnAccentSecondary,
        ControlStrokeColorOnAccentTertiary,
        ControlStrokeColorOnAccentDisabled,

        ControlStrokeColorForStrongFillWhenOnImage,

        CardStrokeColorDefault,
        CardStrokeColorDefaultSolid,

        ControlStrongStrokeColorDefault,
        ControlStrongStrokeColorDisabled,

        SurfaceStrokeColorDefault,
        SurfaceStrokeColorFlyOut,
        SurfaceStrokeColorInverse,

        DividerStrokeColorDefault,

        FocusStrokeColorOuter,
        FocusStrokeColorInner,

        CardBackgroundFillColorDefault,
        CardBackgroundFillColorSecondary,

        SmokeFillColorDefault,

        LayerFillColorDefault,
        LayerFillColorAlt,

        LayerOnAcrylicFillColorDefault,
        LayerOnAccentAcrylicFillColorDefault,

        SolidBackgroundFillColorSecondary,
        SolidBackgroundFillColorTertiary,
        SolidBackgroundFillColorQuarternary,

        SystemFillColorSuccess,
        SystemFillColorCaution,
        SystemFillColorCritical,
        SystemFillColorNeutral,
        SystemFillColorSolidNeutral,
        SystemFillColorAttentionBackground,
        SystemFillColorSuccessBackground,
        SystemFillColorCautionBackground,
        SystemFillColorCriticalBackground,
        SystemFillColorNeutralBackground,
        SystemFillColorSolidAttentionBackground,
        SystemFillColorSolidNeutralBackground,
    };

    explicit WinUI3Style(QObject *parent = nullptr);
    ~WinUI3Style() override;

    WinUI3Style(const WinUI3Style &) = delete;
    WinUI3Style &operator=(const WinUI3Style &) = delete;

    WinUI3Style(WinUI3Style &&) noexcept = delete;
    WinUI3Style &operator=(WinUI3Style &&) noexcept = delete;

    static WinUI3Style *qmlAttachedProperties(QObject *object);

    Theme theme() const noexcept;
    void setTheme(Theme theme);
    void inheritTheme(Theme theme);
    void propagateTheme();
    void resetTheme();

    QVariant accent() const noexcept;
    void setAccent(const QVariant &accent);
    void inheritAccent(QRgb accent);
    void propagateAccent();
    void resetAccent();

    Q_INVOKABLE QColor color(WinUI3Style::Color color) const;

    QColor textFillColorPrimary() const noexcept;
    QColor textFillColorSecondary() const noexcept;
    QColor textFillColorTertiary() const noexcept;
    QColor textFillColorDisabled() const noexcept;
    QColor textFillColorInverse() const noexcept;

    QColor accentTextFillColorDisabled() const noexcept;

    QColor textOnAccentFillColorSelectedText() const noexcept;
    QColor textOnAccentFillColorPrimary() const noexcept;
    QColor textOnAccentFillColorSecondary() const noexcept;
    QColor textOnAccentFillColorDisabled() const noexcept;

    QColor controlFillColorDefault() const noexcept;
    QColor controlFillColorSecondary() const noexcept;
    QColor controlFillColorTertiary() const noexcept;
    QColor controlFillColorDisabled() const noexcept;
    QColor controlFillColorTransparent() const noexcept;
    QColor controlFillColorInputActive() const noexcept;

    QColor controlStrongFillColorDefault() const noexcept;
    QColor controlStrongFillColorDisabled() const noexcept;

    QColor controlSolidFillColorDefault() const noexcept;

    QColor subtleFillColorTransparent() const noexcept;
    QColor subtleFillColorSecondary() const noexcept;
    QColor subtleFillColorTertiary() const noexcept;
    QColor subtleFillColorDisabled() const noexcept;

    QColor controlOnImageFillColorDefault() const noexcept;
    QColor controlOnImageFillColorSecondary() const noexcept;
    QColor controlOnImageFillColorTertiary() const noexcept;
    QColor controlOnImageFillColorDisabled() const noexcept;

    QColor accentFillColorPrimary() const noexcept;
    QColor accentFillColorSecondary() const noexcept;
    QColor accentFillColorTertiary() const noexcept;
    QColor accentFillColorDisabled() const noexcept;

    QColor controlStrokeColorDefault() const noexcept;
    QColor controlStrokeColorSecondary() const noexcept;

    QColor controlStrokeColorOnAccentDefault() const noexcept;
    QColor controlStrokeColorOnAccentSecondary() const noexcept;
    QColor controlStrokeColorOnAccentTertiary() const noexcept;
    QColor controlStrokeColorOnAccentDisabled() const noexcept;

    QColor controlStrokeColorForStrongFillWhenOnImage() const noexcept;

    QColor cardStrokeColorDefault() const noexcept;
    QColor cardStrokeColorDefaultSolid() const noexcept;

    QColor controlStrongStrokeColorDefault() const noexcept;
    QColor controlStrongStrokeColorDisabled() const noexcept;

    QColor surfaceStrokeColorDefault() const noexcept;
    QColor surfaceStrokeColorFlyOut() const noexcept;
    QColor surfaceStrokeColorInverse() const noexcept;

    QColor dividerStrokeColorDefault() const noexcept;

    QColor focusStrokeColorOuter() const noexcept;
    QColor focusStrokeColorInner() const noexcept;

    QColor cardBackgroundFillColorDefault() const noexcept;
    QColor cardBackgroundFillColorSecondary() const noexcept;

    QColor smokeFillColorDefault() const noexcept;

    QColor layerFillColorDefault() const noexcept;
    QColor layerFillColorAlt() const noexcept;

    QColor layerOnAcrylicFillColorDefault() const noexcept;
    QColor layerOnAccentAcrylicFillColorDefault() const noexcept;

    QColor solidBackgroundFillColorSecondary() const noexcept;
    QColor solidBackgroundFillColorTertiary() const noexcept;
    QColor solidBackgroundFillColorQuarternary() const noexcept;

    QColor systemFillColorSuccess() const noexcept;
    QColor systemFillColorCaution() const noexcept;
    QColor systemFillColorCritical() const noexcept;
    QColor systemFillColorNeutral() const noexcept;
    QColor systemFillColorSolidNeutral() const noexcept;
    QColor systemFillColorAttentionBackground() const noexcept;
    QColor systemFillColorSuccessBackground() const noexcept;
    QColor systemFillColorCautionBackground() const noexcept;
    QColor systemFillColorCriticalBackground() const noexcept;
    QColor systemFillColorNeutralBackground() const noexcept;
    QColor systemFillColorSolidAttentionBackground() const noexcept;
    QColor systemFillColorSolidNeutralBackground() const noexcept;

    QColor systemColor(SystemColor role) const;

    QString iconFont() const noexcept;

    static void initGlobals();

  Q_SIGNALS:
    void themeChanged(WinUI3Style::Theme theme);
    void accentChanged(QVariant accent);
    void paletteChanged();
    void iconFontChanged(QString iconFont);

  protected:
    void attachedParentChange(QQuickAttachedObject *new_parent,
                              QQuickAttachedObject *old_parent) override;

  private:
    bool variantToRgba(const QVariant &var, const char *name, QRgb *rgba) const;

    bool m_explicit_theme  = false;
    bool m_explicit_accent = false;

    Theme m_theme = Theme::Light;
    QRgb m_accent = Qt::blue;
};

#include "WinUI3Style.inl"
