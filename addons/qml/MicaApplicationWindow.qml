import QtQuick 6.3
import QtQuick.Controls 6.3

import WinUI3Style 1.0
import WinUI3Style.Addons.Impl 1.0 as Impl

Impl.MicaApplicationWindow {
    id: window

    darkTheme: window.WinUI3Style.theme === WinUI3Style.Theme.Dark

    color: WinUI3Style.systemFillColorSolidNeutralBackground

    Drawer {
        objectName: "__INTERNAL__drawer_side_menu__"

        readonly property bool persistant: sideMenu && showSideMenu

        enabled: sideMenu
        contentItem: sideMenu

        y: (persistant) ? contentPosition : 0

        width: (persistant) ? 320 : 300
        height: (persistant) ? window.height - contentPosition : window.height

        topPadding: (persistant) ? 0 : contentPosition
        interactive: !persistant && enabled
        modal: !persistant && enabled
        position: !persistant && enabled ? 0 : 1
        visible: persistant && enabled
    }
}
