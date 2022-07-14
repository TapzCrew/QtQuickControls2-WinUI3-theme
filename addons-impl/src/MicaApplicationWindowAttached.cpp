#include "MicaApplicationWindow.hpp"

#include <QtQuickTemplates2/private/qquickcontrol_p_p.h>
#include <QtQuickTemplates2/private/qquicktextarea_p.h>
#include <QtQuickTemplates2/private/qquicktextfield_p.h>

struct MicaApplicationWindowAttachedPrivate: public QObjectPrivate {
    auto windowChange(QQuickWindow *wnd) -> void;
    auto activeFocusChange() -> void;

    QQuickWindow *window             = nullptr;
    QQuickItem *active_focus_control = nullptr;

    Q_DECLARE_PUBLIC(MicaApplicationWindowAttached)
};

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
auto MicaApplicationWindowAttachedPrivate::windowChange(QQuickWindow *wnd) -> void {
    Q_Q(MicaApplicationWindowAttached);

    if (window == wnd) return;

    auto old_window = qobject_cast<MicaApplicationWindow *>(window);
    if (old_window && !MicaApplicationWindowPrivate::get(old_window)) old_window = nullptr;

    if (old_window) {
        disconnect(old_window,
                   &MicaApplicationWindow::activeFocusControlChanged,
                   this,
                   &MicaApplicationWindowAttachedPrivate::activeFocusChange);

        QObject::disconnect(old_window,
                            &MicaApplicationWindow::titleBarChanged,
                            q,
                            &MicaApplicationWindowAttached::titleBarChanged);
        QObject::disconnect(old_window,
                            &MicaApplicationWindow::headerChanged,
                            q,
                            &MicaApplicationWindowAttached::headerChanged);
        QObject::disconnect(old_window,
                            &MicaApplicationWindow::menuBarChanged,
                            q,
                            &MicaApplicationWindowAttached::menuBarChanged);
        QObject::disconnect(old_window,
                            &MicaApplicationWindow::footerChanged,
                            q,
                            &MicaApplicationWindowAttached::footerChanged);
        QObject::disconnect(old_window,
                            &MicaApplicationWindow::sideMenuChanged,
                            q,
                            &MicaApplicationWindowAttached::sideMenuChanged);

        QObject::disconnect(old_window,
                            &MicaApplicationWindow::darkThemeEnabledChanged,
                            q,
                            &MicaApplicationWindowAttached::darkThemeEnabledChanged);
        QObject::disconnect(old_window,
                            &MicaApplicationWindow::titleBarExpandedChanged,
                            q,
                            &MicaApplicationWindowAttached::titleBarExpandedChanged);
        QObject::disconnect(old_window,
                            &MicaApplicationWindow::titleBarHeightChanged,
                            q,
                            &MicaApplicationWindowAttached::titleBarHeightChanged);
        QObject::disconnect(old_window,
                            &MicaApplicationWindow::contentPositionChanged,
                            q,
                            &MicaApplicationWindowAttached::contentPositionChanged);
        QObject::disconnect(old_window,
                            &MicaApplicationWindow::micaEnabledChanged,
                            q,
                            &MicaApplicationWindowAttached::micaEnabledChanged);
        QObject::disconnect(old_window,
                            &MicaApplicationWindow::showSideMenuChanged,
                            q,
                            &MicaApplicationWindowAttached::showSideMenuChanged);
    } else if (window)
        disconnect(window,
                   &QQuickWindow::activeFocusItemChanged,
                   this,
                   &MicaApplicationWindowAttachedPrivate::activeFocusChange);

    auto new_window = qobject_cast<MicaApplicationWindow *>(wnd);
    if (new_window) {
        connect(new_window,
                &MicaApplicationWindow::activeFocusControlChanged,
                this,
                &MicaApplicationWindowAttachedPrivate::activeFocusChange);

        QObject::connect(new_window,
                         &MicaApplicationWindow::titleBarChanged,
                         q,
                         &MicaApplicationWindowAttached::titleBarChanged);
        QObject::connect(new_window,
                         &MicaApplicationWindow::headerChanged,
                         q,
                         &MicaApplicationWindowAttached::headerChanged);
        QObject::connect(new_window,
                         &MicaApplicationWindow::menuBarChanged,
                         q,
                         &MicaApplicationWindowAttached::menuBarChanged);
        QObject::connect(new_window,
                         &MicaApplicationWindow::footerChanged,
                         q,
                         &MicaApplicationWindowAttached::footerChanged);
        QObject::connect(new_window,
                         &MicaApplicationWindow::sideMenuChanged,
                         q,
                         &MicaApplicationWindowAttached::sideMenuChanged);

        QObject::connect(new_window,
                         &MicaApplicationWindow::darkThemeEnabledChanged,
                         q,
                         &MicaApplicationWindowAttached::darkThemeEnabledChanged);
        QObject::connect(new_window,
                         &MicaApplicationWindow::titleBarExpandedChanged,
                         q,
                         &MicaApplicationWindowAttached::titleBarExpandedChanged);
        QObject::connect(new_window,
                         &MicaApplicationWindow::titleBarHeightChanged,
                         q,
                         &MicaApplicationWindowAttached::titleBarHeightChanged);
        QObject::connect(new_window,
                         &MicaApplicationWindow::contentPositionChanged,
                         q,
                         &MicaApplicationWindowAttached::contentPositionChanged);
        QObject::connect(new_window,
                         &MicaApplicationWindow::micaEnabledChanged,
                         q,
                         &MicaApplicationWindowAttached::micaEnabledChanged);
        QObject::connect(new_window,
                         &MicaApplicationWindow::showSideMenuChanged,
                         q,
                         &MicaApplicationWindowAttached::showSideMenuChanged);
    } else if (wnd)
        connect(wnd,
                &QQuickWindow::activeFocusItemChanged,
                this,
                &MicaApplicationWindowAttachedPrivate::activeFocusChange);

    window = wnd;

    emit q->windowChanged();
    emit q->contentItemChanged();

    activeFocusChange();

    if ((old_window && old_window->titleBar()) || (new_window && new_window->titleBar()))
        emit q->titleBarChanged(q->titleBar());

    if ((old_window && old_window->header()) || (new_window && new_window->header()))
        emit q->headerChanged(q->header());

    if ((old_window && old_window->menuBar()) || (new_window && new_window->menuBar()))
        emit q->menuBarChanged(q->menuBar());

    if ((old_window && old_window->footer()) || (new_window && new_window->footer()))
        emit q->footerChanged(q->footer());

    if ((old_window && old_window->sideMenu()) || (new_window && new_window->sideMenu()))
        emit q->sideMenuChanged(q->sideMenu());
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttachedPrivate::activeFocusChange() -> void {
    using QQuickItemPtr = QQuickItem *;

    Q_Q(MicaApplicationWindowAttached);

    auto control = QQuickItemPtr { nullptr };
    if (auto app_window = qobject_cast<MicaApplicationWindow *>(window); app_window)
        control = app_window->activeFocusControl();
    else if (window)
        control = findActiveFocusControl(window);

    if (active_focus_control == control) return;

    active_focus_control = control;

    emit q->activeFocusControlChanged(active_focus_control);
}

/////////////////////////////////////
/////////////////////////////////////
MicaApplicationWindowAttached::MicaApplicationWindowAttached(QObject *parent)
    : QObject { *(new MicaApplicationWindowAttachedPrivate {}), parent } {
    Q_D(MicaApplicationWindowAttached);

    if (auto item = qobject_cast<QQuickItem *>(parent)) {
        d->windowChange(item->window());

        QObjectPrivate::connect(item,
                                &QQuickItem::windowChanged,
                                d,
                                &MicaApplicationWindowAttachedPrivate::windowChange);

        if (!d->window) {
            auto p = item;
            while (p) {
                if (auto popup = qobject_cast<QQuickPopup *>(p->parent())) {
                    d->windowChange(popup->window());

                    QObjectPrivate::connect(popup,
                                            &QQuickPopup::windowChanged,
                                            d,
                                            &MicaApplicationWindowAttachedPrivate::windowChange);
                }

                p = p->parentItem();
            }
        }
    } else if (QQuickPopup *popup = qobject_cast<QQuickPopup *>(parent)) {
        d->windowChange(popup->window());

        QObjectPrivate::connect(popup,
                                &QQuickPopup::windowChanged,
                                d,
                                &MicaApplicationWindowAttachedPrivate::windowChange);
    }
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::window() const noexcept -> MicaApplicationWindow * {
    Q_D(const MicaApplicationWindowAttached);

    return qobject_cast<MicaApplicationWindow *>(d->window);
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::contentItem() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->contentItem();

    return nullptr;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::activeFocusControl() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->activeFocusControl();

    return nullptr;
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::titleBar() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->titleBar();

    return nullptr;
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::header() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->header();

    return nullptr;
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::menuBar() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->menuBar();

    return nullptr;
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::footer() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->footer();

    return nullptr;
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::sideMenu() const noexcept -> QQuickItem * {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->sideMenu();

    return nullptr;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::isDarkThemeEnabled() const noexcept -> bool {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->isDarkThemeEnabled();

    return false;
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::isTitleBarExpanded() const noexcept -> bool {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->isTitleBarExpanded();

    return false;
}
/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::titleBarHeight() const noexcept -> int {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->titleBarHeight();

    return 0;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::contentPosition() const noexcept -> int {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->contentPosition();

    return 0;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::isMicaEnabled() const noexcept -> bool {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->isMicaEnabled();

    return false;
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaApplicationWindowAttached::showSideMenu() const noexcept -> bool {
    Q_D(const MicaApplicationWindowAttached);

    if (auto window = qobject_cast<MicaApplicationWindow *>(d->window); window)
        return window->showSideMenu();

    return false;
}
