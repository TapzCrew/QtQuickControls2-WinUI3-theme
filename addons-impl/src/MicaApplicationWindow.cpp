// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include "MicaApplicationWindow.hpp"

#include <QDebug>

#include <QtCore/QScopedValueRollback>
#include <QtCore/private/qobject_p.h>

#include <QtGui/QGuiApplication>

#include <QtQml/QQmlComponent>

#include <QtQuick/QQuickItem>

#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qquickitemchangelistener_p.h>

#include <QtQuickTemplates2/private/qquickbutton_p.h>
#include <QtQuickTemplates2/private/qquickcontentitem_p.h>
#include <QtQuickTemplates2/private/qquickcontrol_p_p.h>
#include <QtQuickTemplates2/private/qquickdeferredexecute_p_p.h>
#include <QtQuickTemplates2/private/qquickdialogbuttonbox_p.h>
#include <QtQuickTemplates2/private/qquickpopup_p_p.h>
#include <QtQuickTemplates2/private/qquicktabbar_p.h>
#include <QtQuickTemplates2/private/qquicktextarea_p.h>
#include <QtQuickTemplates2/private/qquicktextfield_p.h>
#include <QtQuickTemplates2/private/qquicktheme_p.h>
#include <QtQuickTemplates2/private/qquicktoolbar_p.h>

#include <dwmapi.h>
#include <windows.h>

#include <deque>

/////////////////////////////////////
/////////////////////////////////////
auto layoutItem(QQuickItem *item, qreal y, qreal width) -> void {
    if (!item) return;

    item->setY(y);

    if (auto p = QQuickItemPrivate::get(item); p && !p->widthValid()) {
        item->setWidth(width);
        p->widthValidFlag = false;
    }
}

/////////////////////////////////////
/////////////////////////////////////
static auto findActiveFocusControl(QQuickWindow *window) -> QQuickItem * {
    auto item = window->activeFocusItem();

    while (item) {
        if (qobject_cast<QQuickControl *>(item) || qobject_cast<QQuickTextField *>(item) ||
            qobject_cast<QQuickTextArea *>(item))
            return item;
        item = item->parentItem();
    }

    return item;
}

/////////////////////////////////////
/////////////////////////////////////
MicaApplicationWindowPrivate::MicaApplicationWindowPrivate() {
    complete = true;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::get(MicaApplicationWindow *window)
    -> MicaApplicationWindowPrivate * {
    return window->d_func();
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::contentData() -> QQmlListProperty<QObject> {
    Q_Q(MicaApplicationWindow);

    return { q->contentItem(),
             q,
             MicaApplicationWindowPrivate::contentDataAppend,
             QQuickItemPrivate::data_count,
             QQuickItemPrivate::data_at,
             QQuickItemPrivate::data_clear };
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::relayout() -> void {
    Q_Q(MicaApplicationWindow);

    if (!complete || inside_relayout) return;

    auto guard = QScopedValueRollback<bool> { inside_relayout, true };

    auto content = q->contentItem();

    const auto menu_bar_height = menu_bar && menu_bar->isVisible() ? menu_bar->height() : 0;
    const auto footer_height   = footer && footer->isVisible() ? footer->height() : 0;
    const auto persistant      = side_menu && drawer && q->showSideMenu();

    const auto width = q->width();

    if (close_button) {
        const auto button_width = close_button->width();
        minimize_button->setX(width - 3 * button_width);
        minimize_button->setY(0);
        minimize_button->setHeight(title_bar_height);

        maximize_button->setX(width - 2 * button_width);
        maximize_button->setY(0);
        maximize_button->setHeight(title_bar_height);

        close_button->setX(width - button_width);
        close_button->setY(0);
        close_button->setHeight(title_bar_height);
    }

    content->setX((persistant) ? drawer->width() : 0);
    content->setY(q->contentPosition());
    content->setWidth((persistant) ? width - drawer->width() : width);
    content->setHeight(q->height() - q->contentPosition() - footer_height);

    layoutItem(title_bar, 0, close_button ? width - close_button->width() * 3 : width);
    layoutItem(menu_bar, title_bar_height, width);
    layoutItem(header, title_bar_height + menu_bar_height, width);
    layoutItem(footer, content->height() - footer_height, width);

    if (background) {
        auto p = QQuickItemPrivate::get(background);

        if (!p->widthValid() && qFuzzyIsNull(background->x())) {
            background->setWidth(q->width());
            p->widthValidFlag = false;
        }
        if (!p->heightValid() && qFuzzyIsNull(background->y())) {
            background->setHeight(q->height());
            p->heightValidFlag = false;
        }
    }
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::itemGeometryChanged([[maybe_unused]] QQuickItem *item,
                                                       [[maybe_unused]] QQuickGeometryChange change,
                                                       [[maybe_unused]] const QRectF &diff)
    -> void {
    relayout();
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::itemVisibilityChanged([[maybe_unused]] QQuickItem *item)
    -> void {
    relayout();
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::itemImplicitWidthChanged([[maybe_unused]] QQuickItem *item)
    -> void {
    relayout();
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::itemImplicitHeightChanged([[maybe_unused]] QQuickItem *item)
    -> void {
    relayout();
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::updateFont(const QFont &f) -> void {
    Q_Q(MicaApplicationWindow);

    if (font == f) return;

    font = f;

    QQuickControlPrivate::updateFontRecur(q->QQuickWindow::contentItem(), f);

    const auto popups = q->findChildren<QQuickPopup *>();
    for (auto popup : popups)
        QQuickControlPrivate::get(static_cast<QQuickControl *>(popup->popupItem()))->inheritFont(f);

    emit q->fontChanged(font);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::setFontHelper(const QFont &f) -> void {
    if (font.resolveMask() == f.resolveMask() && font == f) return;

    updateFont(f);
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::resolveFont() -> void {
    auto resolved_font = font.resolve(QQuickTheme::font(QQuickTheme::System));

    setFontHelper(resolved_font);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::_q_updateActiveFocus() -> void {
    Q_Q(MicaApplicationWindow);

    setActiveFocusControl(findActiveFocusControl(q));
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::setActiveFocusControl(QQuickItem *item) -> void {
    Q_Q(MicaApplicationWindow);

    if (active_focus_control == item) return;

    active_focus_control = item;

    emit q->activeFocusControlChanged(active_focus_control);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::contentDataAppend(QQmlListProperty<QObject> *prop, QObject *obj)
    -> void {
    QQuickItemPrivate::data_append(prop, obj);

    if (auto popup = qobject_cast<QQuickPopup *>(obj); popup)
        QQuickPopupPrivate::get(popup)->setWindow(static_cast<MicaApplicationWindow *>(prop->data));
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::cancelBackground() -> void {
    Q_Q(MicaApplicationWindow);

    quickCancelDeferred(q, BACKGROUND_NAME);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::executeBackground(bool complete) -> void {
    Q_Q(MicaApplicationWindow);

    if (background.wasExecuted()) return;

    if (!background || complete) quickBeginDeferred(q, BACKGROUND_NAME, background);

    if (complete) quickCompleteDeferred(q, BACKGROUND_NAME, background);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::defaultPalette() const -> QPalette {
    return QQuickTheme::palette(QQuickTheme::System);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowPrivate::updateChildrenPalettes(const QPalette &parentPalette) -> void {
    QQuickWindowPrivate::updateChildrenPalettes(parentPalette);

    for (auto &&popup : q_func()->findChildren<QQuickPopup *>())
        QQuickPopupPrivate::get(popup)->inheritPalette(parentPalette);
}
/////////////////////////////////////
/////////////////////////////////////
MicaApplicationWindow::MicaApplicationWindow(QWindow *parent)
    : QQuickWindowQmlImpl { *(new MicaApplicationWindowPrivate {}), parent }, m_win_addons {
          reinterpret_cast<HWND>(this->winId())
      } {
    Q_D(MicaApplicationWindow);

    connect(this, SIGNAL(activeFocusItemChanged()), this, SLOT(_q_updateActiveFocus()));

    const auto hwnd = reinterpret_cast<HWND>(this->winId());
    Q_ASSERT(hwnd);

    const auto style = WS_CLIPCHILDREN | WS_CAPTION | WS_OVERLAPPED | WS_THICKFRAME |
                       WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    SetWindowLongW(hwnd, GWL_STYLE, style);

    EnableMenuItem(GetSystemMenu(hwnd, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

    d->is_mica_enabled = m_win_addons.windowsVersion().build_number >= 22000;
    m_win_addons.setMicaEnabled(d->is_mica_enabled);

    if (d->is_mica_enabled) setColor(Qt::transparent);

    connect(this, &QQuickWindow::colorChanged, this, [this](const QColor &color) {
        if (color == Qt::transparent) return;

        Q_D(MicaApplicationWindow);

        blockSignals(true);

        d->explicit_color = color;
        if (d->is_mica_enabled) setColor(Qt::transparent);

        blockSignals(false);
    });

    d->resize_frame_width = ::GetSystemMetrics(SM_CXBORDER);

    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

    QMetaObject::invokeMethod(this, &MicaApplicationWindow::initChrome, Qt::QueuedConnection);
    // initChrome();
}

/////////////////////////////////////
/////////////////////////////////////
MicaApplicationWindow::~MicaApplicationWindow() {
    Q_D(MicaApplicationWindow);

    d->setActiveFocusControl(nullptr);

    disconnect(this, SIGNAL(activeFocusItemChanged()), this, SLOT(_q_updateActiveFocus()));
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::qmlAttachedProperties(QObject *object)
    -> MicaApplicationWindowAttached * {
    return new MicaApplicationWindowAttached { object };
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::background() const noexcept -> QQuickItem * {
    auto d = const_cast<MicaApplicationWindowPrivate *>(d_func());

    if (!d->background) d->executeBackground();

    return d->background;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setBackground(QQuickItem *background) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->background == background) return;

    if (!d->background.isExecuting()) d->cancelBackground();

    QQuickControlPrivate::hideOldItem(d->background);

    d->background = background;

    if (background) {
        background->setParentItem(QQuickWindow::contentItem());

        if (qFuzzyIsNull(background->z())) background->setZ(-1);

        if (isComponentComplete()) d->relayout();
    }
    if (!d->background.isExecuting()) emit backgroundChanged(d->background);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::contentItem() const noexcept -> QQuickItem * {
    auto d = const_cast<MicaApplicationWindowPrivate *>(d_func());

    if (!d->app_window_content_item) {
        d->app_window_content_item = new QQuickContentItem { this, QQuickWindow::contentItem() };
        d->app_window_content_item->setFlag(QQuickItem::ItemIsFocusScope);
        d->app_window_content_item->setFocus(true);

        d->relayout();
    }
    return d->app_window_content_item;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::activeFocusControl() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindow);

    return d->active_focus_control;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::titleBar() const noexcept -> QQuickItem * {
    auto d = const_cast<MicaApplicationWindowPrivate *>(d_func());

    return d->title_bar;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setTitleBar(QQuickItem *title_bar) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->title_bar == title_bar) return;

    if (d->title_bar) {
        QQuickItemPrivate::get(d->title_bar)->removeItemChangeListener(d, ITEM_CHANGES);
        d->title_bar->setParentItem(nullptr);
    }

    d->title_bar = title_bar;

    if (title_bar) {
        title_bar->setParentItem(QQuickWindow::contentItem());

        auto p = QQuickItemPrivate::get(title_bar);
        p->addItemChangeListener(d, ITEM_CHANGES);

        if (qFuzzyIsNull(title_bar->z())) title_bar->setZ(4);
    }

    if (isComponentComplete()) d->relayout();

    emit titleBarChanged(d->title_bar);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::header() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindow);

    return d->header;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setHeader(QQuickItem *header) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->header == header) return;

    if (d->header) {
        QQuickItemPrivate::get(d->header)->removeItemChangeListener(d, ITEM_CHANGES);
        d->header->setParentItem(nullptr);
    }
    d->header = header;
    if (header) {
        header->setParentItem(QQuickWindow::contentItem());

        auto p = QQuickItemPrivate::get(header);
        p->addItemChangeListener(d, ITEM_CHANGES);

        if (qFuzzyIsNull(header->z())) header->setZ(3);

        if (auto tool_bar = qobject_cast<QQuickToolBar *>(header); tool_bar)
            tool_bar->setPosition(QQuickToolBar::Header);
        else if (auto tab_bar = qobject_cast<QQuickTabBar *>(header); tab_bar)
            tab_bar->setPosition(QQuickTabBar::Header);
        else if (auto button_box = qobject_cast<QQuickDialogButtonBox *>(header); button_box)
            button_box->setPosition(QQuickDialogButtonBox::Header);
    }

    if (isComponentComplete()) d->relayout();

    emit headerChanged(d->header);
    emit contentPositionChanged(contentPosition());
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::menuBar() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindow);

    return d->menu_bar;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setMenuBar(QQuickItem *menu_bar) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->menu_bar == menu_bar) return;

    if (d->menu_bar) {
        QQuickItemPrivate::get(d->menu_bar)->removeItemChangeListener(d, ITEM_CHANGES);
        d->menu_bar->setParentItem(nullptr);
    }

    d->menu_bar = menu_bar;

    if (menu_bar) {
        menu_bar->setParentItem(QQuickWindow::contentItem());

        auto p = QQuickItemPrivate::get(menu_bar);
        p->addItemChangeListener(d, ITEM_CHANGES);

        if (qFuzzyIsNull(menu_bar->z())) menu_bar->setZ(2);
    }

    if (isComponentComplete()) d->relayout();

    emit menuBarChanged(d->menu_bar);
    emit contentPositionChanged(contentPosition());
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::footer() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindow);

    return d->footer;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setFooter(QQuickItem *footer) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->footer == footer) return;

    if (d->footer) {
        QQuickItemPrivate::get(d->footer)->removeItemChangeListener(d, ITEM_CHANGES);
        d->footer->setParentItem(nullptr);
    }

    d->footer = footer;

    if (footer) {
        footer->setParentItem(contentItem());

        auto p = QQuickItemPrivate::get(footer);
        p->addItemChangeListener(d, ITEM_CHANGES);

        if (qFuzzyIsNull(footer->z())) footer->setZ(1);

        if (auto tool_bar = qobject_cast<QQuickToolBar *>(footer); tool_bar)
            tool_bar->setPosition(QQuickToolBar::Footer);
        else if (auto tab_bar = qobject_cast<QQuickTabBar *>(footer); tab_bar)
            tab_bar->setPosition(QQuickTabBar::Footer);
        else if (auto button_box = qobject_cast<QQuickDialogButtonBox *>(footer); button_box)
            button_box->setPosition(QQuickDialogButtonBox::Footer);
    }

    if (isComponentComplete()) d->relayout();

    emit footerChanged(d->footer);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::sideMenu() const noexcept -> QQuickItem * {
    auto d = const_cast<MicaApplicationWindowPrivate *>(d_func());

    return d->side_menu;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setSideMenu(QQuickItem *side_menu) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->side_menu == side_menu) return;

    d->side_menu = side_menu;

    if (isComponentComplete()) d->relayout();

    emit sideMenuChanged(d->side_menu);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::font() const noexcept -> const QFont & {
    Q_D(const MicaApplicationWindow);

    return d->font;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setFont(const QFont &font) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->font.resolveMask() == font.resolveMask() && d->font == font) return;

    auto resolved_font = font.resolve(QQuickTheme::font(QQuickTheme::System));

    d->setFontHelper(resolved_font);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::resetFont() noexcept -> void {
    setFont(QFont());
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::locale() const noexcept -> const QLocale & {
    Q_D(const MicaApplicationWindow);

    return d->locale;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setLocale(const QLocale &locale) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->locale == locale) return;

    d->locale = locale;

    QQuickControlPrivate::updateLocaleRecur(QQuickWindow::contentItem(), locale);

    // TODO: internal QQuickPopupManager that provides reliable access to all QQuickPopup
    // instances
    const auto popups = QQuickWindow::contentItem()->findChildren<QQuickPopup *>();
    for (auto popup : popups)
        QQuickControlPrivate::get(static_cast<QQuickControl *>(popup->popupItem()))
            ->updateLocale(locale, false); // explicit=false

    emit localeChanged(d->locale);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::resetLocale() noexcept -> void {
    setLocale(QLocale());
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::isDarkThemeEnabled() const noexcept -> bool {
    auto d = const_cast<MicaApplicationWindowPrivate *>(d_func());

    return d->is_dark_theme_enabled;
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setDarkThemeEnabled(bool enabled) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->is_dark_theme_enabled == enabled) return;

    m_win_addons.setDarkModeEnabled(enabled);

    d->is_dark_theme_enabled = enabled;
    emit darkThemeEnabledChanged(d->is_dark_theme_enabled);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::isTitleBarExpanded() const noexcept -> bool {
    auto d = const_cast<MicaApplicationWindowPrivate *>(d_func());

    return d->title_bar_expanded;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setTitleBarExpanded(bool expanded) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->title_bar_expanded == expanded) return;

    d->title_bar_expanded = expanded;
    d->title_bar_height =
        (d->title_bar_expanded) ? EXPANDED_TITLE_BAR_SIZE : DEFAULT_TITLE_BAR_SIZE;

    emit titleBarExpandedChanged(d->title_bar_expanded);
    emit titleBarHeightChanged(d->title_bar_height);
    emit contentPositionChanged(contentPosition());
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::titleBarHeight() const noexcept -> int {
    auto d = const_cast<MicaApplicationWindowPrivate *>(d_func());

    return d->title_bar_height;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::contentPosition() const noexcept -> int {
    auto d = const_cast<MicaApplicationWindowPrivate *>(d_func());

    const auto &menu_bar = d->menu_bar;
    const auto &header   = d->header;

    const auto menu_bar_height = menu_bar && menu_bar->isVisible() ? menu_bar->height() : 0;
    const auto header_height   = header && header->isVisible() ? header->height() : 0;

    return d->title_bar_height + menu_bar_height + header_height;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::isMicaEnabled() const noexcept -> bool {
    auto d = const_cast<MicaApplicationWindowPrivate *>(d_func());

    return d->is_mica_enabled;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::showSideMenu() const noexcept -> bool {
    Q_D(const MicaApplicationWindow);

    return width() >= 800 && d->side_menu;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::openSideMenu() noexcept -> void {
    Q_D(MicaApplicationWindow);

    d->drawer->open();
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::closeSideMenu() noexcept -> void {
    Q_D(MicaApplicationWindow);

    d->drawer->close();
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::setMicaEnabled(bool enabled) noexcept -> void {
    Q_D(MicaApplicationWindow);

    if (d->is_mica_enabled == enabled) return;

    d->is_mica_enabled = enabled;

    m_win_addons.setMicaEnabled(d->is_mica_enabled);

    if (d->is_mica_enabled) setColor(Qt::transparent);
    else
        setColor(d->explicit_color);

    emit micaEnabledChanged(d->is_mica_enabled);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::isComponentComplete() const noexcept -> bool {
    Q_D(const MicaApplicationWindow);

    return d->complete;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::classBegin() noexcept -> void {
    Q_D(MicaApplicationWindow);

    d->complete = false;

    QQuickWindowQmlImpl::classBegin();

    d->resolveFont();
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::componentComplete() noexcept -> void {
    Q_D(MicaApplicationWindow);

    d->complete = true;

    d->executeBackground(true);

    QQuickWindowQmlImpl::componentComplete();

    d->relayout();
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::resizeEvent(QResizeEvent *event) noexcept -> void {
    Q_D(MicaApplicationWindow);

    QQuickWindowQmlImpl::resizeEvent(event);

    d->relayout();

    emit showSideMenuChanged(width() >= 800);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::nativeEvent(const QByteArray &type, void *message, qintptr *result)
    -> bool {
    Q_D(MicaApplicationWindow);

    auto msg               = reinterpret_cast<MSG *>(message);
    const auto pixel_ratio = effectiveDevicePixelRatio();

    const auto XFRAME_WIDTH = GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);
    const auto YFRAME_WIDTH = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);

    const auto caption_size =
        QSizeF { (d->close_button)
                     ? (width() * pixel_ratio) - (d->close_button->width() * pixel_ratio) * 3
                     : width() * pixel_ratio,
                 static_cast<qreal>(d->title_bar_height) * pixel_ratio };
    const auto caption_pos = QPoint { 0, 0 };

    if (msg->message == WM_NCCALCSIZE) {
        if (msg->wParam != 0) {
            auto rect = reinterpret_cast<RECT *>(msg->lParam);

            if (d->maximized) rect->top += YFRAME_WIDTH;
            rect->right -= XFRAME_WIDTH;
            rect->left += XFRAME_WIDTH;
            rect->bottom -= YFRAME_WIDTH;

            return true;
        }
    } else if (msg->message == WM_SIZE) {
        if (msg->wParam == SIZE_MAXIMIZED) d->maximized = true;
        else if (msg->wParam == SIZE_RESTORED || msg->wParam == SIZE_MINIMIZED)
            d->maximized = false;
        SetWindowPos(msg->hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
    } else if (msg->message == WM_NCHITTEST) {
        auto mouse_position = POINT { static_cast<LONG>(LOWORD(msg->lParam)),
                                      static_cast<LONG>(HIWORD(msg->lParam)) };
        ScreenToClient(msg->hwnd, &mouse_position);

        auto rect = RECT {};
        ZeroMemory(&rect, sizeof(RECT));

        GetClientRect(msg->hwnd, &rect);

        const auto actual_width  = rect.right - rect.left;
        const auto actual_height = rect.bottom - rect.top;

        const auto is_top    = mouse_position.y < YFRAME_WIDTH;
        const auto is_bottom = mouse_position.y > actual_height + XFRAME_WIDTH;
        const auto is_left   = mouse_position.x < -YFRAME_WIDTH;
        const auto is_right  = mouse_position.x > actual_width + XFRAME_WIDTH;

        if (is_top && !d->maximized) {
            if (is_left) *result = HTTOPLEFT;
            else if (is_right)
                *result = HTTOPRIGHT;
            else
                *result = HTTOP;
        } else if (is_bottom && !d->maximized) {
            if (is_left) *result = HTBOTTOMLEFT;
            else if (is_right)
                *result = HTBOTTOMRIGHT;
            else
                *result = HTBOTTOM;
        } else if (is_left && !d->maximized)
            *result = HTLEFT;
        else if (is_right && !d->maximized)
            *result = HTRIGHT;
        else if ((mouse_position.y <= caption_size.height()) &&
                 (mouse_position.x >= caption_pos.x()) &&
                 (mouse_position.x <= caption_pos.x() + caption_size.width()) &&
                 !hitWidgetTest(mouse_position.x, mouse_position.y))
            *result = HTCAPTION;
        else
            return QQuickWindowQmlImpl::nativeEvent(type, message, result);

        return true;
    } else if (msg->message == WM_SETTINGCHANGE || msg->message == WM_THEMECHANGED)
        setDarkThemeEnabled(m_win_addons.isSystemDarkModeEnabled());

    return QQuickWindowQmlImpl::nativeEvent(type, message, result);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::hitWidgetTest(int x, int y) -> bool {
    Q_D(MicaApplicationWindow);

    const auto pixel_ratio = effectiveDevicePixelRatio();

    const auto caption = d->title_bar;
    if (!caption) return false;

    auto dequeu = std::deque<QQuickItem *> {};
    dequeu.push_front(caption);
    while (!std::empty(dequeu)) {
        const auto child = dequeu.back();
        dequeu.pop_back();

        for (const auto &_child : child->childItems()) dequeu.push_front(_child);

        if (!child->inherits("QQuickControl")) { continue; }

        const auto rect = QRectF { child->x(),
                                   child->y(),
                                   static_cast<qreal>(child->width()),
                                   static_cast<qreal>(child->height()) };

        const auto pos = QPointF { x / pixel_ratio, y / pixel_ratio };

        if (rect.contains(pos.toPoint())) return true;
    }

    return false;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindow::initChrome() -> void {
    Q_D(MicaApplicationWindow);

    auto root = contentItem();
    for (auto child : root->children())
        if (child->objectName() == "__INTERNAL__drawer_side_menu__") {
            d->drawer = qobject_cast<QQuickDrawer *>(child);
            d->drawer->setParentItem(QQuickWindow::contentItem());
        }

    auto engine = qmlEngine(d->drawer);

    const auto button_uri = QUrl { u"qrc:/qml/ChromeButton.qml"_qs };
    auto button_component = QQmlComponent { engine, button_uri };
    if (button_component.isError()) qDebug() << button_component.errorString();

    d->minimize_button = qobject_cast<QQuickItem *>(button_component.create());
    QQmlEngine::setObjectOwnership(d->minimize_button, QQmlEngine::CppOwnership);

    d->minimize_button->setParent(engine);
    d->minimize_button->setParentItem(QQuickWindow::contentItem());
    d->minimize_button->setProperty("glyph", 0xe921);
    d->minimize_button->setWidth(48);

    auto minimize_button = qobject_cast<QQuickButton *>(d->minimize_button);
    connect(minimize_button, &QQuickButton::clicked, this, &QQuickWindow::showMinimized);

    d->maximize_button = qobject_cast<QQuickItem *>(button_component.create());
    QQmlEngine::setObjectOwnership(d->maximize_button, QQmlEngine::CppOwnership);

    d->maximize_button->setParent(engine);
    d->maximize_button->setParentItem(QQuickWindow::contentItem());
    d->maximize_button->setProperty("glyph", 0xe922);
    d->maximize_button->setWidth(48);

    auto maximize_button = qobject_cast<QQuickButton *>(d->maximize_button);
    connect(maximize_button, &QQuickButton::clicked, this, [this, maximize_button]() {
        if (visibility() != QWindow::Maximized) {
            showMaximized();
            maximize_button->setProperty("glyph", 0xe923);
        } else {
            showNormal();
            maximize_button->setProperty("glyph", 0xe922);
        }
    });

    d->close_button = qobject_cast<QQuickItem *>(button_component.create());
    QQmlEngine::setObjectOwnership(d->close_button, QQmlEngine::CppOwnership);

    d->close_button->setParent(engine);
    d->close_button->setParentItem(QQuickWindow::contentItem());
    d->close_button->setProperty("glyph", 0xe8bb);
    d->close_button->setProperty("chromeColor", QColor { "#c32b1c" });
    d->close_button->setWidth(48);

    auto close_button = qobject_cast<QQuickButton *>(d->close_button);
    connect(close_button, &QQuickButton::clicked, this, &QQuickWindow::close);

    d->relayout();
}

#include <moc_MicaApplicationWindow.cpp>
