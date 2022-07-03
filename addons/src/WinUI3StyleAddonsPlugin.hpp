// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include <QtCore/QObject>
#include <QtQml/QQmlExtensionPlugin>

class WinUI3StyleAddonsPlugin: public QQmlEngineExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

  public:
    explicit WinUI3StyleAddonsPlugin(QObject *parent = nullptr);
    ~WinUI3StyleAddonsPlugin() override;

    WinUI3StyleAddonsPlugin(const WinUI3StyleAddonsPlugin &) = delete;
    auto operator=(const WinUI3StyleAddonsPlugin &) -> WinUI3StyleAddonsPlugin & = delete;

    WinUI3StyleAddonsPlugin(WinUI3StyleAddonsPlugin &&) noexcept = delete;
    auto operator=(WinUI3StyleAddonsPlugin &&) noexcept -> WinUI3StyleAddonsPlugin & = delete;
};
