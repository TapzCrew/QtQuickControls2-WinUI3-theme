import QtQuick 6.3
import QtQuick.Templates 6.3 as T
import QtQuick.Controls.impl 6.3

import WinUI3Style 1.0
import WinUI3Style.Impl 1.0

T.ToolButton {
    id: control

    rightPadding: 14
    leftPadding: 14

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    spacing: 8

    icon.color: internal.contentColor

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

        color: internal.contentColor
    }

    background: Rectangle {
        radius: 4

        implicitHeight: 29
        implicitWidth: 64

        id: button

        color: WinUI3Style.subtleFillColorTransparent
    }

    states: [
        State {
            name: "disabled"
            when: !control.enabled
        },
        State {
            name: "idle"
            when: control.enabled && !control.down && !control.hovered
        },
        State {
            name: "pushed"
            when: control.down
        },
        State {
            name: "hovered"
            when: control.hovered
        }
    ]

    transitions: [
        Transition {
            to: "disabled"

            ColorAnimation {
                target: button
                property: "color"

                to: control.WinUI3Style.subtleFillColorDisabled

                duration: internal.colorTransitionsDuration

                easing.type: Easing.OutQuad
            }
        },
        Transition {
            to: "idle"

            ColorAnimation {
                target: button
                property: "color"

                to: control.WinUI3Style.subtleFillColorTransparent

                duration: internal.colorTransitionsDuration

                easing.type: Easing.OutQuad
            }
        },
        Transition {
            to: "pushed"

            ColorAnimation {
                target: button
                property: "color"

                to: control.WinUI3Style.subtleFillColorTertiary

                duration: internal.colorTransitionsDuration

                easing.type: Easing.OutQuad
            }
        },
        Transition {
            to: "hovered"

            ColorAnimation {
                target: button
                property: "color"

                to: control.WinUI3Style.subtleFillColorSecondary

                duration: internal.colorTransitionsDuration

                easing.type: Easing.OutQuad
            }
        }
    ]

    QtObject {
        id: internal

        readonly property int colorTransitionsDuration: 100

        readonly property color contentColor: {
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
