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
    WinUI3StylePlugin(QObject *parent = nullptr);
    auto name() const noexcept -> QString override;
    auto initializeTheme(QQuickTheme *theme) noexcept -> void override;

  private:
    WinUI3Theme m_theme;
};
