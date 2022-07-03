// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include "WinUI3StyleAddonsImplPlugin.hpp"

#include <QSurfaceFormat>

void qml_register_types_WinUI3Style_Addons_Impl();

/////////////////////////////////////
/////////////////////////////////////
WinUI3StyleAddonsImplPlugin::WinUI3StyleAddonsImplPlugin(QObject *parent)
    : QQmlEngineExtensionPlugin { parent } {
    [[maybe_unused]] volatile auto registration = &qml_register_types_WinUI3Style_Addons_Impl;
}

/////////////////////////////////////
/////////////////////////////////////
WinUI3StyleAddonsImplPlugin::~WinUI3StyleAddonsImplPlugin() = default;
