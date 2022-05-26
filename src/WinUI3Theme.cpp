// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

#include "WinUI3Theme.mpp"

#include <QtGui/qfontinfo.h>
#include <QtQuickTemplates2/private/qquicktheme_p.h>

static const auto FONT_NAME = QStringLiteral("Segoe UI");

/////////////////////////////////////
/////////////////////////////////////
auto WinUI3Theme::initialize(QQuickTheme *theme) -> void {
    auto system_font          = QFont {};
    auto group_box_title_font = QFont {};
    auto tab_button_font      = QFont {};

    const auto font = QFont { FONT_NAME };

    const auto font_family = QFontInfo { font }.family();
    if (font_family == FONT_NAME) {
        const auto families = QStringList { font.family() };
        system_font.setFamilies(families);
        group_box_title_font.setFamilies(families);
        tab_button_font.setFamilies(families);
    }

    system_font.setPixelSize(15);
    theme->setFont(QQuickTheme::System, system_font);

    group_box_title_font.setPixelSize(15);
    group_box_title_font.setWeight(QFont::DemiBold);
    theme->setFont(QQuickTheme::GroupBox, group_box_title_font);

    tab_button_font.setPixelSize(24);
    tab_button_font.setWeight(QFont::Light);
    theme->setFont(QQuickTheme::TabBar, tab_button_font);
}
