// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#pragma once

#include <QtCore/QObject>
#include <QtQml/QQmlExtensionPlugin>

class WinUI3StyleAddonsImplPlugin: public QQmlEngineExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

  public:
    explicit WinUI3StyleAddonsImplPlugin(QObject *parent = nullptr);
    ~WinUI3StyleAddonsImplPlugin() override;

    WinUI3StyleAddonsImplPlugin(const WinUI3StyleAddonsImplPlugin &) = delete;
    auto operator=(const WinUI3StyleAddonsImplPlugin &) -> WinUI3StyleAddonsImplPlugin & = delete;

    WinUI3StyleAddonsImplPlugin(WinUI3StyleAddonsImplPlugin &&) noexcept = delete;
    auto operator                        =(WinUI3StyleAddonsImplPlugin &&) noexcept
        -> WinUI3StyleAddonsImplPlugin & = delete;
};
