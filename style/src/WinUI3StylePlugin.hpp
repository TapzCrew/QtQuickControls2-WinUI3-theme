// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include <QtCore/QObject>
#include <QtQuickControls2/private/qquickstyleplugin_p.h>

#include "WinUI3Theme.mpp"

class QQuickTheme;
class WinUI3StylePlugin: public QQuickStylePlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

  public:
    explicit WinUI3StylePlugin(QObject *parent = nullptr);
    ~WinUI3StylePlugin() override;

    WinUI3StylePlugin(const WinUI3StylePlugin &) = delete;
    WinUI3StylePlugin &operator=(const WinUI3StylePlugin &) = delete;

    WinUI3StylePlugin(WinUI3StylePlugin &&) noexcept = delete;
    WinUI3StylePlugin &operator=(WinUI3StylePlugin &&) noexcept = delete;

    QString name() const noexcept override;
    void initializeTheme(QQuickTheme *theme) noexcept override;

  private:
    WinUI3Theme m_theme;
};
