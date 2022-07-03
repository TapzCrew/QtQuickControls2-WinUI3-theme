// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include "WinUI3StyleImplPlugin.hpp"

void qml_register_types_WinUI3Style_Impl();

/////////////////////////////////////
/////////////////////////////////////
WinUI3StyleImplPlugin::WinUI3StyleImplPlugin(QObject *parent)
    : QQmlEngineExtensionPlugin { parent } {
    [[maybe_unused]] volatile auto registration = &qml_register_types_WinUI3Style_Impl;
}

/////////////////////////////////////
/////////////////////////////////////
WinUI3StyleImplPlugin::~WinUI3StyleImplPlugin() = default;
