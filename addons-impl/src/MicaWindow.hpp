// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#pragma once

#include <QtQuickTemplates2/private/qquickapplicationwindow_p.h>

#include "WinAddons.mpp"

QT_BEGIN_NAMESPACE

class QQuickItem;

QT_END_NAMESPACE

class MicaWindowAttached;
class MicaWindow: public QQuickApplicationWindow {
    Q_OBJECT

    Q_PROPERTY(bool darkTheme READ isDarkThemeEnabled WRITE setDarkThemeEnabled NOTIFY
                   darkThemeEnabledChanged FINAL)
    Q_PROPERTY(bool titleBarExpanded READ isTitleBarExpanded WRITE setTitleBarExpanded NOTIFY
                   titleBarExpandedChanged FINAL)
    Q_PROPERTY(int titleBarHeight READ titleBarHeight NOTIFY titleBarHeightChanged FINAL)
    Q_PROPERTY(bool mica READ isMicaEnabled WRITE setMicaEnabled NOTIFY micaEnabledChanged FINAL)

    QML_NAMED_ELEMENT(MicaWindow)
    QML_ATTACHED(MicaWindowAttached)
  public:
    explicit MicaWindow(QWindow *parent = nullptr);
    ~MicaWindow() override;

    auto isDarkThemeEnabled() const noexcept -> bool;
    auto setDarkThemeEnabled(bool enabled) noexcept -> void;

    auto isTitleBarExpanded() const noexcept -> bool;
    auto setTitleBarExpanded(bool expanded) noexcept -> void;

    auto titleBarHeight() const noexcept -> int;

    auto setMicaEnabled(bool enabled) noexcept -> void;
    auto isMicaEnabled() const noexcept -> bool;

  Q_SIGNALS:
    auto darkThemeEnabledChanged(bool enabled) -> void;
    auto titleBarExpandedChanged(bool expanded) -> void;
    auto titleBarHeightChanged(int height) -> void;
    auto micaEnabledChanged(bool enabled) -> void;

  private:
    auto nativeEvent(const QByteArray &eventpeype, void *message, qintptr *result) -> bool override;
    auto hitWidgetTest(int x, int y) -> bool;

    WinAddons m_win_addons;

    bool m_is_dark_theme_enabled;
    bool m_is_mica_enabled;

    bool m_title_bar_expanded;
    int m_title_bar_height;

    bool m_maximized;

    QColor m_explicit_color;
};

class MicaWindowAttached: public QQuickApplicationWindowAttached {
    Q_OBJECT

  public:
    using QQuickApplicationWindowAttached::QQuickApplicationWindowAttached;
};

QML_DECLARE_TYPE(MicaWindow)
QML_DECLARE_TYPEINFO(MicaWindow, QML_HAS_ATTACHED_PROPERTIES)

#include "MicaWindow.inl"
