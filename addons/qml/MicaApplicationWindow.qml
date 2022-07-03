import QtQuick 6.3
import QtQuick.Layouts 6.3
import QtQuick.Controls 6.3

import WinUI3Style 1.0
import WinUI3Style.Impl 1.0
import WinUI3Style.Addons.Impl 1.0

MicaWindow {
    id: window

    darkTheme: window.WinUI3Style.theme === WinUI3Style.Theme.Dark

    default property alias content: content_widgets.children
    property alias titlebar: titlebar_widgets.children

    property alias sideMenuContent: sidemenu.contentItem
    property bool enableSideMenu: false

    readonly property bool showSideMenu: window.width > 800

    function openSideMenu() {
        sidemenu.open()
    }
    function closeSideMenu() {
        sidemenu.close()
    }

    color: WinUI3Style.systemFillColorSolidNeutralBackground

    Item {
        id: root
        anchors.fill: parent

        RowLayout {
            id: window_titlebar

            anchors.top: root.top
            anchors.right: root.right
            anchors.left: root.left

            height: window.titleBarHeight

            onVisibleChanged: console.log(visibility)

            Row {
                id: titlebar_widgets
                objectName: "caption"

                Layout.fillHeight: true
                Layout.fillWidth: true

                Layout.margins: 4
            }

            ChromeButton {
                id: minimize_button

                darkThemeEnabled: window.darkTheme

                button_type: ChromeButton.Type.Minimize

                onClicked: window.showMinimized()

                expanded: window.titleBarExpanded

                active: window.active

                Layout.alignment: Qt.AlignTop
            }

            ChromeButton {
                id: maximize_button

                darkThemeEnabled: window.darkTheme

                button_type: (window.visibility === Window.Maximized) ? ChromeButton.Type.Restore : ChromeButton.Type.Maximize

                onClicked: {
                    if (button_type === ChromeButton.Type.Maximize)
                        window.showMaximized()
                    else if (button_type === ChromeButton.Type.Restore)
                        window.showNormal()
                }

                expanded: window.titleBarExpanded
                active: window.active
                Layout.alignment: Qt.AlignTop
            }

            ChromeButton {
                id: close_button

                darkThemeEnabled: window.darkTheme

                button_type: ChromeButton.Type.Close

                onClicked: window.close()

                expanded: window.titleBarExpanded
                active: window.active
                Layout.alignment: Qt.AlignTop
            }
        }

        Drawer {
            readonly property bool persistant: enableSideMenu && showSideMenu

            id: sidemenu

            enabled: enableSideMenu

            y: (persistant) ? window_titlebar.height : 0

            width: (persistant) ? 320 : 300
            height: (persistant) ? window.height - window_titlebar.height : window.height

            topPadding: (persistant) ? 0 : window_titlebar.height
            interactive: !persistant && enableSideMenu
            modal: !persistant && enableSideMenu
            position: !persistant && enableSideMenu ? 0 : 1
            visible: persistant && enableSideMenu
        }

        Item {
            id: content_widgets

            anchors.top: window_titlebar.bottom
            anchors.right: root.right
            anchors.bottom: root.bottom

            width: (showSideMenu) ? parent.width - sidemenu.width : parent.width

            anchors.margins: 0
        }

        QtObject {
            id: internal
        }
    }
}
