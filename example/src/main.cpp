// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>

#include <iostream>

auto main(int argc, char *argv[]) -> int {
    auto app = QGuiApplication { argc, argv };

    auto format = QSurfaceFormat::defaultFormat();
    format.setAlphaBufferSize(8);

    QSurfaceFormat::setDefaultFormat(format);

    QQuickWindow::setDefaultAlphaBuffer(true);

    auto engine = QQmlApplicationEngine {};

    const auto url = QUrl { u"qrc:///qml/Main.qml"_qs };

    QQuickWindow::setDefaultAlphaBuffer(true);
    QQuickStyle::setStyle("WinUI3Style");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
