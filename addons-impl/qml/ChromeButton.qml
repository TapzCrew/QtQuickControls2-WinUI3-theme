import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0
import WinUI3Style.Impl 1.0
import WinUI3Style.Addons.Impl 1.0

T.Button {
    id: control

    property bool active: true

    property int glyph: 0
    property color chromeColor: control.WinUI3Style.accent

    property bool useSystemFocusVisuals: true

    font.family: "Segoe Fluent Icons"
    font.pixelSize: 10

    text: String.fromCharCode(glyph)

    contentItem: Text {
        id: text

        font: control.font
        text: control.text

        color: {
            if (!control.active && !control.hovered && !control.down) {
                if (control.WinUI3Style.theme === WinUI3Style.Dark)
                    return control.WinUI3Style.color(
                                control.WinUI3Style.AccentLight2)
                else
                    return control.WinUI3Style.color(
                                control.WinUI3Style.AccentDark1)
            }

            if (control.down)
                return "#C5FFFFFF"

            if (control.hovered)
                return "white"

            return control.WinUI3Style.textFillColorPrimary
        }

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        anchors.fill: parent

        border.width: 0

        color: {
            if (control.hovered)
                return chromeColor

            return "transparent"
        }
    }
}
