// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include <QtCore/QString>
#include <QtQuickTemplates2/private/qquicktheme_p.h>

#include "WinUI3StylePlugin.hpp"
#include "WinUI3Theme.mpp"

extern auto qml_register_types_org_tapzcrew_win32() -> void;
Q_GHS_KEEP_REFERENCE(qml_register_types_org_tapzcrew_win32);

/////////////////////////////////////
/////////////////////////////////////
WinUI3StylePlugin::WinUI3StylePlugin(QObject *parent) : QQuickStylePlugin { parent } {
    [[maybe_unused]] volatile auto registration = &qml_register_types_org_tapzcrew_win32;
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3StylePlugin::name() const noexcept -> QString {
    return QStringLiteral("WinUI3");
}

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3StylePlugin::initializeTheme(QQuickTheme *theme) noexcept -> void {
    m_theme.initialize(theme);
}
