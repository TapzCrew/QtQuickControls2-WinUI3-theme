// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include "MicaWindow.hpp"
#include "qnamespace.h"

#include <QDebug>

#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickItem>

#include <dwmapi.h>
#include <windows.h>

#include <deque>

static constexpr auto RESIZE_FRAME_WIDTH      = 8;
static constexpr auto DEFAULT_TITLE_BAR_SIZE  = 32;
static constexpr auto EXPANDED_TITLE_BAR_SIZE = 48;

/////////////////////////////////////
/////////////////////////////////////
MicaWindow::MicaWindow(QWindow *parent)
    : QQuickApplicationWindow { parent }, m_win_addons { reinterpret_cast<HWND>(this->winId()) },
      m_is_dark_theme_enabled { false }, m_is_mica_enabled { true }, m_title_bar_expanded { false },
      m_title_bar_height { 32 } {
    const auto hwnd = reinterpret_cast<HWND>(this->winId());
    Q_ASSERT(hwnd);

    const auto style = WS_CLIPCHILDREN | WS_CAPTION | WS_OVERLAPPED | WS_THICKFRAME |
                       WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    SetWindowLongW(hwnd, GWL_STYLE, style);

    EnableMenuItem(GetSystemMenu(hwnd, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

    m_win_addons.setMicaEnabled(m_is_mica_enabled);
    setColor(Qt::transparent);

    connect(this, &QQuickWindow::colorChanged, this, [this](const QColor &color) {
        if (color == Qt::transparent) return;

        blockSignals(true);

        m_explicit_color = color;
        if (m_is_mica_enabled) setColor(Qt::transparent);

        blockSignals(false);
    });

    m_resize_frame_width = ::GetSystemMetrics(SM_CXBORDER);

    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
}

/////////////////////////////////////
/////////////////////////////////////
MicaWindow::~MicaWindow() = default;

/////////////////////////////////////
/////////////////////////////////////
auto MicaWindow::setDarkThemeEnabled(bool enabled) noexcept -> void {
    if (m_is_dark_theme_enabled == enabled) return;

    m_win_addons.setDarkModeEnabled(enabled);

    m_is_dark_theme_enabled = enabled;
    emit darkThemeEnabledChanged(m_is_dark_theme_enabled);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaWindow::setTitleBarExpanded(bool expanded) noexcept -> void {
    if (m_title_bar_expanded == expanded) return;

    m_title_bar_expanded = expanded;
    m_title_bar_height = (m_title_bar_expanded) ? EXPANDED_TITLE_BAR_SIZE : DEFAULT_TITLE_BAR_SIZE;

    emit titleBarExpandedChanged(m_title_bar_expanded);
    emit titleBarHeightChanged(m_title_bar_height);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaWindow::setMicaEnabled(bool enabled) noexcept -> void {
    if (m_is_mica_enabled == enabled) return;

    m_is_mica_enabled = enabled;

    m_win_addons.setMicaEnabled(m_is_mica_enabled);

    if (m_is_mica_enabled) setColor(Qt::transparent);
    else
        setColor(m_explicit_color);

    emit micaEnabledChanged(m_is_mica_enabled);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaWindow::nativeEvent(const QByteArray &type, void *message, qintptr *result) -> bool {
    auto msg               = reinterpret_cast<MSG *>(message);
    const auto pixel_ratio = effectiveDevicePixelRatio();

    const auto XFRAME_WIDTH = GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);
    const auto YFRAME_WIDTH = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);

    const auto caption      = qobject_cast<QQuickItem *>(findChild<QObject *>("caption"));
    const auto caption_size = [&] {
        if (caption)
            return QSizeF { caption->width() * pixel_ratio, caption->height() * pixel_ratio }
                .toSize();

        return QSize {};
    }();
    const auto caption_pos = [&] {
        if (caption)
            return QPointF { caption->x() * pixel_ratio, caption->y() * pixel_ratio }.toPoint();

        return QPoint {};
    }();

    if (msg->message == WM_NCCALCSIZE) {
        if (msg->wParam != 0) {
            auto rect = reinterpret_cast<RECT *>(msg->lParam);

            if (m_maximized) rect->top += YFRAME_WIDTH;
            rect->right -= XFRAME_WIDTH;
            rect->left += XFRAME_WIDTH;
            rect->bottom -= YFRAME_WIDTH;

            return true;
        }
    } else if (msg->message == WM_SIZE) {
        if (msg->wParam == SIZE_MAXIMIZED) m_maximized = true;
        else if (msg->wParam == SIZE_RESTORED || msg->wParam == SIZE_MINIMIZED)
            m_maximized = false;
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

        const auto is_top    = mouse_position.y < m_resize_frame_width;
        const auto is_bottom = mouse_position.y > actual_height + m_resize_frame_width;
        const auto is_left   = mouse_position.x < -m_resize_frame_width;
        const auto is_right  = mouse_position.x > actual_width + m_resize_frame_width;

        if (is_top && !m_maximized) {
            if (is_left) *result = HTTOPLEFT;
            else if (is_right)
                *result = HTTOPRIGHT;
            else
                *result = HTTOP;
        } else if (is_bottom && !m_maximized) {
            if (is_left) *result = HTBOTTOMLEFT;
            else if (is_right)
                *result = HTBOTTOMRIGHT;
            else
                *result = HTBOTTOM;
        } else if (is_left && !m_maximized)
            *result = HTLEFT;
        else if (is_right && !m_maximized)
            *result = HTRIGHT;
        else if ((mouse_position.y <= caption_size.height()) &&
                 (mouse_position.x >= caption_pos.x()) &&
                 (mouse_position.x <= caption_pos.x() + caption_size.width()) &&
                 !hitWidgetTest(mouse_position.x, mouse_position.y))
            *result = HTCAPTION;
        else
            return QQuickApplicationWindow::nativeEvent(type, message, result);

        return true;
    } else if (msg->message == WM_SETTINGCHANGE || msg->message == WM_THEMECHANGED)
        setDarkThemeEnabled(m_win_addons.isSystemDarkModeEnabled());

    return QQuickApplicationWindow::nativeEvent(type, message, result);
}

/////////////////////////////////////
/////////////////////////////////////
auto MicaWindow::hitWidgetTest(int x, int y) -> bool {
    const auto pixel_ratio = effectiveDevicePixelRatio();

    const auto caption = qobject_cast<QQuickItem *>(findChild<QObject *>("caption"));

    auto dequeu = std::deque<QQuickItem *> {};
    dequeu.push_front(caption);
    while (!std::empty(dequeu)) {
        const auto child = dequeu.back();
        dequeu.pop_back();

        for (const auto &_child : child->childItems()) dequeu.push_front(_child);

        if (!child->inherits("QQuickControl")) { continue; }

        const auto rect = QRectF { child->x() + caption->x(),
                                   child->y() + caption->y(),
                                   static_cast<qreal>(child->width()),
                                   static_cast<qreal>(child->height()) };

        const auto pos = QPointF { x / pixel_ratio, y / pixel_ratio };

        if (rect.contains(pos.toPoint())) return true;
    }

    return false;
}
