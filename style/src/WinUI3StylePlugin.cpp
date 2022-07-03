// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include <QtCore/QString>
#include <QtQuickTemplates2/private/qquicktheme_p.h>

#include "WinUI3Style.hpp"
#include "WinUI3StylePlugin.hpp"

void qml_register_types_WinUI3Style();

/////////////////////////////////////
/////////////////////////////////////
WinUI3StylePlugin::WinUI3StylePlugin(QObject *parent) : QQuickStylePlugin { parent } {
    [[maybe_unused]] volatile auto registration = &qml_register_types_WinUI3Style;
}

/////////////////////////////////////
/////////////////////////////////////
WinUI3StylePlugin::~WinUI3StylePlugin() = default;

/////////////////////////////////////
/////////////////////////////////////
QString WinUI3StylePlugin::name() const noexcept {
    return QStringLiteral("WinUI3Style");
}

/////////////////////////////////////
/////////////////////////////////////
void WinUI3StylePlugin::initializeTheme(QQuickTheme *theme) noexcept {
    WinUI3Style::initGlobals();

    m_theme.initialize(theme);
}
