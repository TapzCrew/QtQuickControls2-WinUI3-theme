// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include "WinUI3Theme.mpp"

#include <QtGui/QFontDatabase>
#include <QtGui/QFontInfo>
#include <QtQuickTemplates2/private/qquicktheme_p.h>

#include <QQuickWindow>

static constexpr auto SEGOE_UI_TEXT_FONT_NAMES = std::array {
    "Segoe UI",
    "Segoe UI Light",
    "Segoe UI Light Italic",
    "Segoe UI Semilight",
    "Segoe UI Italic",
    "Segoe UI Semibold",
    "Segoe UI Semibold Italic",
    "Segoe UI Bold",
    "Segoe UI Bold Italic",
    "Segoe UI Black",
    "Segoe UI Black Italic",
};

/////////////////////////////////////
/////////////////////////////////////
void WinUI3Theme::initialize(QQuickTheme *theme) {
    QFontDatabase::addApplicationFont(":/fonts/SegoeIcons.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segoeui.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouib.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouib.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouii.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouil.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouisl.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouiz.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouibl.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouibli.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouiemj.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouihis.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouili.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouisb.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouisbi.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouisli.ttf");
    QFontDatabase::addApplicationFont(":/fonts/segouisym.ttf");
    QFontDatabase::addApplicationFont(":/fonts/SegUIVar.ttf");

    auto system_font          = QFont { SEGOE_UI_TEXT_FONT_NAMES[0] };
    auto group_box_title_font = QFont { SEGOE_UI_TEXT_FONT_NAMES[5] };
    auto tab_button_font      = QFont { SEGOE_UI_TEXT_FONT_NAMES[1] };

    system_font.setPixelSize(14);
    system_font.setWeight(QFont::Weight::Normal);
    theme->setFont(QQuickTheme::System, system_font);

    group_box_title_font.setPixelSize(15);
    group_box_title_font.setWeight(QFont::DemiBold);
    theme->setFont(QQuickTheme::GroupBox, group_box_title_font);

    tab_button_font.setPixelSize(24);
    tab_button_font.setWeight(QFont::Light);
    theme->setFont(QQuickTheme::TabBar, tab_button_font);

    auto format = QSurfaceFormat::defaultFormat();
    format.setAlphaBufferSize(8);

    QSurfaceFormat::setDefaultFormat(format);
    QQuickWindow::setDefaultAlphaBuffer(true);
    // QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);
}
