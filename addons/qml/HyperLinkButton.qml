import QtQuick 6.3
import QtQuick.Templates 6.3 as T
import QtQuick.Controls.impl 6.3

import WinUI3Style 1.0
import WinUI3Style.Impl 1.0

T.ToolButton {
    id: control

    rightPadding: 14
    leftPadding: 14

    //topPadding: 12
    //bottomPadding: 12
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    spacing: 8

    icon.color: internal.contentColor()

    property string link: ""
    property bool useSystemFocusVisuals: true

    onClicked: Qt.openUrlExternally(link)

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font

        color: internal.contentColor()
    }

    background: Rectangle {
        radius: 4

        implicitHeight: 29
        implicitWidth: 64

        id: button

        color: WinUI3Style.subtleFillColorTransparent
    }

    state: (!control.enabled) ? "NONE" : (control.down) ? "PUSHED" : (control.hovered) ? "HOVERED" : "RELEASED"
    states: [
        State {
            name: "NONE"
            PropertyChanges {
                target: button
                color: control.WinUI3Style.subtleFillColorDisabled
            }
        },
        State {
            name: "RELEASED"
            PropertyChanges {
                target: button
                color: control.WinUI3Style.subtleFillColorTransparent
            }
        },
        State {
            name: "PUSHED"
            PropertyChanges {
                target: button
                color: control.WinUI3Style.subtleFillColorTertiary
            }
        },
        State {
            name: "HOVERED"
            PropertyChanges {
                target: button
                color: control.WinUI3Style.subtleFillColorSecondary
            }
        }
    ]

    transitions: [
        Transition {
            from: "*"
            to: "NONE"

            ColorAnimation {
                target: button
                easing.type: Easing.InOutQuad
                duration: 100
            }
        },
        Transition {
            from: "*"
            to: "RELEASED"

            ColorAnimation {
                target: button
                easing.type: Easing.InOutQuad
                duration: 100
            }
        },
        Transition {
            from: "*"
            to: "PUSHED"

            ColorAnimation {
                target: button
                easing.type: Easing.InOutQuad
                duration: 100
            }
        },
        Transition {
            from: "*"
            to: "HOVERED"

            ColorAnimation {
                target: button
                easing.type: Easing.InOutQuad
                duration: 100
            }
        }
    ]

    QtObject {
        id: internal

        function contentColor() {
            if (!control.enabled)
                return control.WinUI3Style.accentFillColorDisabled

            if (control.down)
                return control.WinUI3Style.accentFillColorTertiary

            if (control.highlighted)
                return control.WinUI3Style.accentFillColorSecondary

            return control.WinUI3Style.accentFillColorPrimary
        }
    }
}
