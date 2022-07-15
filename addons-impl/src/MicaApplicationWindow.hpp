// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#pragma once

#include <QtQuick/private/qquickpositioners_p.h>
#include <QtQuick/private/qquickwindowmodule_p_p.h>

#include <QtQuickLayouts/private/qquicklinearlayout_p.h>

#include <QtQuickTemplates2/private/qquickdrawer_p.h>

#include <QtQuick/private/qquickwindowmodule_p.h>

#include <QtQuickTemplates2/private/qquickdeferredpointer_p_p.h>
#include <QtQuickTemplates2/private/qtquicktemplates2global_p.h>

#include <QtCore/QLocale>
#include <QtGui/QFont>
#include <QtGui/QPalette>

#include "WinAddons.mpp"
#include "qevent.h"

static constexpr auto RESIZE_FRAME_WIDTH      = 8;
static constexpr auto DEFAULT_TITLE_BAR_SIZE  = 32;
static constexpr auto EXPANDED_TITLE_BAR_SIZE = 48;
static constexpr auto ITEM_CHANGES = QQuickItemPrivate::Visibility | QQuickItemPrivate::Geometry |
                                     QQuickItemPrivate::ImplicitWidth |
                                     QQuickItemPrivate::ImplicitHeight;
static constexpr auto BACKGROUND_NAME = "background";

class MicaApplicationWindow;
struct MicaApplicationWindowPrivate;
class MicaApplicationWindowAttached;

class MicaApplicationWindow: public QQuickWindowQmlImpl {
    Q_OBJECT

    Q_PROPERTY(
        QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged FINAL)
    Q_PROPERTY(QQuickItem *contentItem READ contentItem CONSTANT FINAL)
    Q_PROPERTY(QQuickItem *activeFocusControl READ activeFocusControl NOTIFY
                   activeFocusControlChanged FINAL)
    Q_PROPERTY(QQuickItem *titleBar READ titleBar WRITE setTitleBar NOTIFY titleBarChanged FINAL)
    Q_PROPERTY(QQuickItem *header READ header WRITE setHeader NOTIFY headerChanged FINAL)
    Q_PROPERTY(QQuickItem *menuBar READ menuBar WRITE setMenuBar NOTIFY menuBarChanged FINAL)
    Q_PROPERTY(QQuickItem *footer READ footer WRITE setFooter NOTIFY footerChanged FINAL)
    Q_PROPERTY(QQuickItem *sideMenu READ sideMenu WRITE setSideMenu NOTIFY sideMenuChanged FINAL)

    Q_PROPERTY(QFont font READ font WRITE setFont RESET resetFont NOTIFY fontChanged FINAL)
    Q_PROPERTY(
        QLocale locale READ locale WRITE setLocale RESET resetLocale NOTIFY localeChanged FINAL)

    Q_PROPERTY(bool darkTheme READ isDarkThemeEnabled WRITE setDarkThemeEnabled NOTIFY
                   darkThemeEnabledChanged FINAL)
    Q_PROPERTY(bool titleBarExpanded READ isTitleBarExpanded WRITE setTitleBarExpanded NOTIFY
                   titleBarExpandedChanged FINAL)
    Q_PROPERTY(int titleBarHeight READ titleBarHeight NOTIFY titleBarHeightChanged FINAL)
    Q_PROPERTY(int contentPosition READ contentPosition NOTIFY contentPositionChanged FINAL)
    Q_PROPERTY(bool mica READ isMicaEnabled WRITE setMicaEnabled NOTIFY micaEnabledChanged FINAL)
    Q_PROPERTY(bool showSideMenu READ showSideMenu NOTIFY showSideMenuChanged FINAL)

    Q_PRIVATE_PROPERTY(MicaApplicationWindow::d_func(),
                       QQmlListProperty<QObject> contentData READ contentData FINAL)
    Q_PRIVATE_PROPERTY(MicaApplicationWindow::d_func(),
                       QQuickPalette *palette READ palette WRITE setPalette RESET resetPalette
                           NOTIFY paletteChanged)

    Q_CLASSINFO("DeferredPropertyNames", "background")
    Q_CLASSINFO("DefaultProperty", "contentData")

    QML_NAMED_ELEMENT(MicaApplicationWindow)
    QML_ATTACHED(MicaApplicationWindowAttached)
  public:
    explicit MicaApplicationWindow(QWindow *parent = nullptr);
    ~MicaApplicationWindow() override;

    MicaApplicationWindow(const MicaApplicationWindow &) = delete;
    auto operator=(const MicaApplicationWindow &) -> MicaApplicationWindow & = delete;

    static auto qmlAttachedProperties(QObject *object) -> MicaApplicationWindowAttached *;

    auto background() const noexcept -> QQuickItem *;
    auto setBackground(QQuickItem *background) noexcept -> void;

    auto contentItem() const noexcept -> QQuickItem *;

    auto activeFocusControl() const noexcept -> QQuickItem *;

    auto titleBar() const noexcept -> QQuickItem *;
    auto setTitleBar(QQuickItem *title_bar) noexcept -> void;

    auto header() const noexcept -> QQuickItem *;
    auto setHeader(QQuickItem *header) noexcept -> void;

    auto menuBar() const noexcept -> QQuickItem *;
    auto setMenuBar(QQuickItem *menu_bar) noexcept -> void;

    auto footer() const noexcept -> QQuickItem *;
    auto setFooter(QQuickItem *footer) noexcept -> void;

    auto sideMenu() const noexcept -> QQuickItem *;
    auto setSideMenu(QQuickItem *side_menu) noexcept -> void;

    auto font() const noexcept -> const QFont &;
    auto setFont(const QFont &font) noexcept -> void;
    auto resetFont() noexcept -> void;

    auto locale() const noexcept -> const QLocale &;
    auto setLocale(const QLocale &locale) noexcept -> void;
    auto resetLocale() noexcept -> void;

    auto isDarkThemeEnabled() const noexcept -> bool;
    auto setDarkThemeEnabled(bool enabled) noexcept -> void;

    auto isTitleBarExpanded() const noexcept -> bool;
    auto setTitleBarExpanded(bool expanded) noexcept -> void;

    auto titleBarHeight() const noexcept -> int;
    auto contentPosition() const noexcept -> int;

    auto setMicaEnabled(bool enabled) noexcept -> void;
    auto isMicaEnabled() const noexcept -> bool;

    auto showSideMenu() const noexcept -> bool;
    Q_SLOT void openSideMenu() noexcept;
    Q_SLOT void closeSideMenu() noexcept;
  Q_SIGNALS:
    auto backgroundChanged(QQuickItem *background) -> void;
    auto activeFocusControlChanged(QQuickItem *activeFocusControl) -> void;
    auto titleBarChanged(QQuickItem *titleBar) -> void;
    auto headerChanged(QQuickItem *header) -> void;
    auto menuBarChanged(QQuickItem *menuBar) -> void;
    auto footerChanged(QQuickItem *footer) -> void;
    auto sideMenuChanged(QQuickItem *sideMenu) -> void;

    auto fontChanged(const QFont &font) -> void;
    auto localeChanged(const QLocale &locale) -> void;

    auto darkThemeEnabledChanged(bool enabled) -> void;
    auto titleBarExpandedChanged(bool expanded) -> void;
    auto titleBarHeightChanged(int height) -> void;
    auto contentPositionChanged(int contentPosition) -> void;
    auto micaEnabledChanged(bool enabled) -> void;
    auto showSideMenuChanged(bool showSideMenu) -> void;

  protected:
    auto isComponentComplete() const noexcept -> bool;
    auto classBegin() noexcept -> void override;
    auto componentComplete() noexcept -> void override;
    auto resizeEvent(QResizeEvent *event) noexcept -> void override;
    auto focusInEvent(QFocusEvent *event) noexcept -> void override;
    auto focusOutEvent(QFocusEvent *event) noexcept -> void override;

  private:
    auto nativeEvent(const QByteArray &eventpeype, void *message, qintptr *result) -> bool override;
    auto hitWidgetTest(int x, int y) -> bool;

    Q_SLOT void initChrome();

    WinAddons m_win_addons;

    Q_DECLARE_PRIVATE(MicaApplicationWindow)
    Q_PRIVATE_SLOT(d_func(), void _q_updateActiveFocus())
};

struct MicaApplicationWindowPrivate: public QQuickWindowQmlImplPrivate,
                                     public QQuickItemChangeListener {
    MicaApplicationWindowPrivate();

    static auto get(MicaApplicationWindow *window) -> MicaApplicationWindowPrivate *;

    auto contentData() -> QQmlListProperty<QObject>;

    auto relayout() -> void;

    auto itemGeometryChanged(QQuickItem *item, QQuickGeometryChange change, const QRectF &diff)
        -> void override;
    auto itemVisibilityChanged(QQuickItem *item) -> void override;
    auto itemImplicitWidthChanged(QQuickItem *item) -> void override;
    auto itemImplicitHeightChanged(QQuickItem *item) -> void override;

    auto updateFont(const QFont &f) -> void;
    auto setFontHelper(const QFont &f) -> void;
    auto resolveFont() -> void;

    auto _q_updateActiveFocus() -> void;
    auto setActiveFocusControl(QQuickItem *item) -> void;

    static auto contentDataAppend(QQmlListProperty<QObject> *prop, QObject *obj) -> void;

    auto cancelBackground() -> void;
    auto executeBackground(bool complete = false) -> void;

    auto defaultPalette() const -> QPalette override;
    auto updateChildrenPalettes(const QPalette &parentPalette) -> void override;

    QQuickDeferredPointer<QQuickItem> background;
    QQuickItem *active_focus_control    = nullptr;
    QQuickItem *app_window_content_item = nullptr;
    QQuickItem *content_item            = nullptr;
    QQuickItem *title_bar               = nullptr;
    QQuickItem *menu_bar                = nullptr;
    std::unique_ptr<QMetaObject::Connection> menu_update_connection;
    QQuickItem *header    = nullptr;
    QQuickItem *footer    = nullptr;
    QQuickItem *side_menu = nullptr;

    QQuickItem *minimize_button = nullptr;
    QQuickItem *maximize_button = nullptr;
    QQuickItem *close_button    = nullptr;

    QQuickDrawer *drawer = nullptr;

    QFont font;
    QLocale locale;

    bool is_dark_theme_enabled = false;
    bool is_mica_enabled       = true;

    bool title_bar_expanded = false;
    int title_bar_height    = DEFAULT_TITLE_BAR_SIZE;
    int content_position    = DEFAULT_TITLE_BAR_SIZE;

    int resize_frame_width = RESIZE_FRAME_WIDTH;

    bool maximized = false;

    QColor explicit_color;

    bool inside_relayout = false;

    Q_DECLARE_PUBLIC(MicaApplicationWindow)
};

struct MicaApplicationWindowAttachedPrivate;

class MicaApplicationWindowAttached: public QObject {
    Q_OBJECT

    Q_PROPERTY(MicaApplicationWindow *window READ window NOTIFY windowChanged FINAL)
    Q_PROPERTY(QQuickItem *contentItem READ contentItem NOTIFY contentItemChanged FINAL)
    Q_PROPERTY(QQuickItem *activeFocusControl READ activeFocusControl NOTIFY
                   activeFocusControlChanged FINAL)
    Q_PROPERTY(QQuickItem *titleBar READ titleBar NOTIFY titleBarChanged FINAL)
    Q_PROPERTY(QQuickItem *header READ header NOTIFY headerChanged FINAL)
    Q_PROPERTY(QQuickItem *menuBar READ menuBar NOTIFY menuBarChanged FINAL)
    Q_PROPERTY(QQuickItem *footer READ footer NOTIFY footerChanged FINAL)
    Q_PROPERTY(QQuickItem *sideMenu READ sideMenu NOTIFY sideMenuChanged FINAL)

    Q_PROPERTY(bool darkTheme READ isDarkThemeEnabled NOTIFY darkThemeEnabledChanged FINAL)
    Q_PROPERTY(bool titleBarExpanded READ isTitleBarExpanded NOTIFY titleBarExpandedChanged FINAL)
    Q_PROPERTY(int titleBarHeight READ titleBarHeight NOTIFY titleBarHeightChanged FINAL)
    Q_PROPERTY(int contentPosition READ contentPosition NOTIFY contentPositionChanged FINAL)
    Q_PROPERTY(bool mica READ isMicaEnabled NOTIFY micaEnabledChanged FINAL)
    Q_PROPERTY(bool showSideMenu READ showSideMenu NOTIFY showSideMenuChanged FINAL)

  public:
    explicit MicaApplicationWindowAttached(QObject *parent = nullptr);

    MicaApplicationWindowAttached(const MicaApplicationWindowAttached &) = delete;
    auto operator                          =(const MicaApplicationWindowAttached &)
        -> MicaApplicationWindowAttached & = delete;

    auto window() const noexcept -> MicaApplicationWindow *;
    auto contentItem() const noexcept -> QQuickItem *;
    auto activeFocusControl() const noexcept -> QQuickItem *;
    auto titleBar() const noexcept -> QQuickItem *;
    auto header() const noexcept -> QQuickItem *;
    auto menuBar() const noexcept -> QQuickItem *;
    auto footer() const noexcept -> QQuickItem *;
    auto sideMenu() const noexcept -> QQuickItem *;

    auto isDarkThemeEnabled() const noexcept -> bool;
    auto isTitleBarExpanded() const noexcept -> bool;
    auto titleBarHeight() const noexcept -> int;
    auto contentPosition() const noexcept -> int;
    auto isMicaEnabled() const noexcept -> bool;
    auto showSideMenu() const noexcept -> bool;

  Q_SIGNALS:
    auto windowChanged() -> void;
    auto contentItemChanged() -> void;
    auto activeFocusControlChanged(QQuickItem *activeFocusControl) -> void;
    auto titleBarChanged(QQuickItem *titleBar) -> void;
    auto headerChanged(QQuickItem *header) -> void;
    auto footerChanged(QQuickItem *footer) -> void;
    auto menuBarChanged(QQuickItem *menuBar) -> void;
    auto sideMenuChanged(QQuickItem *sideMenu) -> void;

    auto darkThemeEnabledChanged(bool darkTheme) -> void;
    auto titleBarExpandedChanged(bool titleBarExpanded) -> void;
    auto titleBarHeightChanged(int titleBarHeight) -> void;
    auto contentPositionChanged(int contentPosition) -> void;
    auto micaEnabledChanged(bool mica) -> void;
    auto showSideMenuChanged(bool showSideMenu) -> void;

  private:
    Q_DECLARE_PRIVATE(MicaApplicationWindowAttached)
};

QML_DECLARE_TYPE(MicaApplicationWindow)
QML_DECLARE_TYPEINFO(MicaApplicationWindow, QML_HAS_ATTACHED_PROPERTIES)
