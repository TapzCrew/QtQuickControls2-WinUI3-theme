// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#pragma once

#include <QtGui/qcolor.h>
#include <QtQuickControls2Impl/private/qquickattachedobject_p.h>

class WinUI3Style: public QQuickAttachedObject {
    Q_OBJECT

    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged FINAL)
    Q_PROPERTY(
        QVariant accent READ accent WRITE setAccent RESET resetAccent NOTIFY accentChanged FINAL)
    Q_PROPERTY(QVariant foreground READ foreground WRITE setForeground RESET resetForeground NOTIFY
                   foregroundChanged FINAL)
    Q_PROPERTY(QVariant background READ background WRITE setBackground RESET resetBackground NOTIFY
                   backgroundChanged FINAL)

    Q_PROPERTY(QColor altHighColor READ altHighColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor altLowColor READ altLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor altMediumColor READ altMediumColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor altMediumHighColor READ altMediumHighColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor altMediumLowColor READ altMediumLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor baseHighColor READ baseHighColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor baseLowColor READ baseLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor baseMediumColor READ baseMediumColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor baseMediumHighColor READ baseMediumHighColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor baseMediumLowColor READ baseMediumLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor chromeAltLowColor READ chromeAltLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor chromeBlackHighColor READ chromeBlackHighColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor chromeBlackLowColor READ chromeBlackLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor chromeBlackMediumLowColor READ chromeBlackMediumLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor chromeBlackMediumColor READ chromeBlackMediumColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor chromeDisabledHighColor READ chromeDisabledHighColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(
        QColor chromeDisabledLowColor READ chromeDisabledLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor chromeHighColor READ chromeHighColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor chromeLowColor READ chromeLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor chromeMediumColor READ chromeMediumColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor chromeMediumLowColor READ chromeMediumLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor chromeWhiteColor READ chromeWhiteColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor listLowColor READ listLowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor listMediumColor READ listMediumColor NOTIFY paletteChanged FINAL)

    QML_NAMED_ELEMENT(WinUI3)
    QML_ATTACHED(WinUI3Style)
    QML_UNCREATABLE("")

  public:
    explicit WinUI3Style(QObject *parent = nullptr);

    static auto qmlAttachedProperties(QObject *object) -> WinUI3Style *;

    enum class Theme { Light, Dark, System };
    Q_ENUM(Theme)

    auto theme() const -> Theme;
    auto setTheme(Theme theme) -> void;
    auto inheritTheme(Theme theme) -> void;
    auto propagateTheme() -> void;
    auto resetTheme() -> void;

    enum class Color {
        Lime,
        Green,
        Emerald,
        Teal,
        Cyan,
        Cobalt,
        Indigo,
        Violet,
        Pink,
        Magenta,
        Crimson,
        Red,
        Orange,
        Amber,
        Yellow,
        Brown,
        Olive,
        Steel,
        Mauve,
        Taupe
    };
    Q_ENUM(Color)

    auto accent() const -> QVariant;
    auto setAccent(const QVariant &accent) -> void;
    auto inheritAccent(QRgb accent) -> void;
    auto propagateAccent() -> void;
    auto resetAccent() -> void;

    auto foreground() const -> QVariant;
    auto setForeground(const QVariant &foreground) -> void;
    auto inheritForeground(QRgb foreground, bool has) -> void;
    auto propagateForeground() -> void;
    auto resetForeground() -> void;

    auto background() const -> QVariant;
    auto setBackground(const QVariant &background) -> void;
    auto inheritBackground(QRgb background, bool has) -> void;
    auto propagateBackground() -> void;
    auto resetBackground() -> void;

    Q_INVOKABLE QColor color(WinUI3Style::Color color) const;

    auto altHighColor() const -> QColor;
    auto altLowColor() const -> QColor;
    auto altMediumColor() const -> QColor;
    auto altMediumHighColor() const -> QColor;
    auto altMediumLowColor() const -> QColor;
    auto baseHighColor() const -> QColor;
    auto baseLowColor() const -> QColor;
    auto baseMediumColor() const -> QColor;
    auto baseMediumHighColor() const -> QColor;
    auto baseMediumLowColor() const -> QColor;
    auto chromeAltLowColor() const -> QColor;
    auto chromeBlackHighColor() const -> QColor;
    auto chromeBlackLowColor() const -> QColor;
    auto chromeBlackMediumLowColor() const -> QColor;
    auto chromeBlackMediumColor() const -> QColor;
    auto chromeDisabledHighColor() const -> QColor;
    auto chromeDisabledLowColor() const -> QColor;
    auto chromeHighColor() const -> QColor;
    auto chromeLowColor() const -> QColor;
    auto chromeMediumColor() const -> QColor;
    auto chromeMediumLowColor() const -> QColor;
    auto chromeWhiteColor() const -> QColor;
    auto listLowColor() const -> QColor;
    auto listMediumColor() const -> QColor;

    enum class SystemColor {
        AltHigh,
        AltLow,
        AltMedium,
        AltMediumHigh,
        AltMediumLow,
        BaseHigh,
        BaseLow,
        BaseMedium,
        BaseMediumHigh,
        BaseMediumLow,
        ChromeAltLow,
        ChromeBlackHigh,
        ChromeBlackLow,
        ChromeBlackMediumLow,
        ChromeBlackMedium,
        ChromeDisabledHigh,
        ChromeDisabledLow,
        ChromeHigh,
        ChromeLow,
        ChromeMedium,
        ChromeMediumLow,
        ChromeWhite,
        ListLow,
        ListMedium
    };

    auto systemColor(SystemColor role) const -> QColor;

    static auto initGlobals() -> void;

  Q_SIGNALS:
    auto themeChanged() -> void;
    auto accentChanged() -> void;
    auto foregroundChanged() -> void;
    auto backgroundChanged() -> void;
    auto paletteChanged() -> void;

  protected:
    auto attachedParentChange(QQuickAttachedObject *new_parent, QQuickAttachedObject *old_parent)
        -> void override;

  private:
    auto variantToRgba(const QVariant &var, const char *name, QRgb *rgba) const -> bool;

    bool m_explicit_theme      = false;
    bool m_explicit_accent     = false;
    bool m_explicit_foreground = false;
    bool m_explicit_background = false;

    bool m_has_foreground = false;
    bool m_has_background = false;

    Theme m_theme     = Theme::Light;
    QRgb m_accent     = Qt::blue;
    QRgb m_foreground = Qt::black;
    QRgb m_background = Qt::white;
};
