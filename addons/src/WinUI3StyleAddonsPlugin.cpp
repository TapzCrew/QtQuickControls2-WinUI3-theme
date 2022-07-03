// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include "WinUI3StyleAddonsPlugin.hpp"

void qml_register_types_WinUI3Style_Addons();

/////////////////////////////////////
/////////////////////////////////////
WinUI3StyleAddonsPlugin::WinUI3StyleAddonsPlugin(QObject *parent)
    : QQmlEngineExtensionPlugin { parent } {
    [[maybe_unused]] volatile auto registration = &qml_register_types_WinUI3Style_Addons;
}

/////////////////////////////////////
/////////////////////////////////////
WinUI3StyleAddonsPlugin::~WinUI3StyleAddonsPlugin() = default;
