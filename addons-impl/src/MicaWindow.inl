// Copyright (C) 2022 Arthur LAURENT <arthur.laurent4@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level of this distribution

/////////////////////////////////////
/////////////////////////////////////
inline auto MicaWindow::isDarkThemeEnabled() const noexcept -> bool {
    return m_is_dark_theme_enabled;
}

/////////////////////////////////////
/////////////////////////////////////
inline auto MicaWindow::isTitleBarExpanded() const noexcept -> bool {
    return m_title_bar_expanded;
}

/////////////////////////////////////
/////////////////////////////////////
inline auto MicaWindow::titleBarHeight() const noexcept -> int {
    return m_title_bar_height;
}

/////////////////////////////////////
/////////////////////////////////////
inline auto MicaWindow::isMicaEnabled() const noexcept -> bool {
    return m_is_mica_enabled;
}
