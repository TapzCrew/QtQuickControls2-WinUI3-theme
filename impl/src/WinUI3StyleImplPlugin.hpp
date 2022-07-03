// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#pragma once

#include <QtCore/QObject>
#include <QtQml/QQmlEngineExtensionPlugin>

class WinUI3StyleImplPlugin: public QQmlEngineExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

  public:
    explicit WinUI3StyleImplPlugin(QObject *parent = nullptr);
    ~WinUI3StyleImplPlugin() override;

    WinUI3StyleImplPlugin(const WinUI3StyleImplPlugin &) = delete;
    auto operator=(const WinUI3StyleImplPlugin &) -> WinUI3StyleImplPlugin & = delete;

    WinUI3StyleImplPlugin(WinUI3StyleImplPlugin &&) noexcept = delete;
    auto operator=(WinUI3StyleImplPlugin &&) noexcept -> WinUI3StyleImplPlugin & = delete;
};
