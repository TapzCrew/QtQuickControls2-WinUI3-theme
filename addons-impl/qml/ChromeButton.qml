import QtQuick 6.3
import QtQuick.Controls 6.3

import WinUI3Style 1.0
import WinUI3Style.Impl 1.0
import WinUI3Style.Addons.Impl 1.0

Item {
    id: root

    signal clicked

    property bool expanded: false
    property bool active: true

    enum Type {
        Minimize,
        Maximize,
        Restore,
        Close
    }

    property int button_type: ChromeButton.Type.Close
    property bool darkThemeEnabled: false

    width: 48
    height: 31

    Button {
        id: button

        anchors.fill: parent

        onReleased: root.clicked()

        font.family: "Segoe Fluent Icons"
        font.pixelSize: 10
        text: {
            if (root.button_type === ChromeButton.Type.Minimize)
                return String.fromCodePoint(0xe921)
            else if (root.button_type === ChromeButton.Type.Maximize)
                return String.fromCodePoint(0xe922)
            else if (root.button_type === ChromeButton.Type.Restore)
                return String.fromCodePoint(0xe923)
            else if (root.button_type === ChromeButton.Type.Close)
                return String.fromCodePoint(0xe8bb)
        }

        contentItem: Text {
            id: text
            font: button.font
            text: button.text
            color: {
                if (!root.active && !button.hovered && !button.down) {
                    if (darkThemeEnabled)
                        return root.WinUI3Style.color(
                                    root.WinUI3Style.AccentLight2)
                    else
                        return root.WinUI3Style.color(
                                    root.WinUI3Style.AccentDark1)
                }

                if (button.down)
                    return "#C5FFFFFF"

                if (button.hovered)
                    return "white"

                return root.WinUI3Style.textFillColorPrimary
            }

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            anchors.fill: parent

            border.width: 0

            color: {
                if (button.hovered) {
                    if (root.button_type === ChromeButton.Type.Close)
                        return "#c32b1c"

                    return WinUI3Style.accent
                }

                return "transparent"
            }
        }
    }
}
