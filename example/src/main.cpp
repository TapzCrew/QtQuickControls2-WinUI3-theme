// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>

#include <iostream>

constexpr auto toString(QSGRendererInterface::GraphicsApi e) {
    switch (e) {
        case QSGRendererInterface::GraphicsApi::Unknown: return "Unknown";
        case QSGRendererInterface::GraphicsApi::Software: return "Software";
        case QSGRendererInterface::GraphicsApi::OpenVG: return "OpenVG";
        case QSGRendererInterface::GraphicsApi::OpenGL: return "OpenGL";
        case QSGRendererInterface::GraphicsApi::Direct3D11: return "Direct3D11";
        case QSGRendererInterface::GraphicsApi::Vulkan: return "Vulkan";
        case QSGRendererInterface::GraphicsApi::Metal: return "Metal";
        case QSGRendererInterface::GraphicsApi::Null: return "Null";
    }

    return "";
}

auto main(int argc, char *argv[]) -> int {
    auto app = QGuiApplication { argc, argv };

    QQuickStyle::setStyle("WinUI3Style");

    auto engine = QQmlApplicationEngine {};

    const auto url = QUrl { u"qrc:///qml/Main.qml"_qs };

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    qDebug() << toString(QQuickWindow::graphicsApi());

    return app.exec();
}
