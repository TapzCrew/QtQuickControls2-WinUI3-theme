import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick.Controls.impl 6.3

import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0
import WinUI3Style.Impl 1.0

T.Button {
    id: control

    rightPadding: 12
    leftPadding: 12
    topPadding: 6
    bottomPadding: 6
    spacing: 8

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    icon.color: internal.contentColor()

    property bool useSystemFocusVisuals: true
    default property alias menuItems: menu.contentChildren

    onClicked: menu.open()

    contentItem: Row {
        spacing: 12

        IconLabel {
            id: label

            clip: true

            spacing: control.spacing
            mirrored: control.mirrored
            display: control.display

            icon: control.icon
            text: control.text
            font: control.font

            anchors.verticalCenter: parent.verticalCenter

            color: internal.contentColor()
        }

        IconLabel {
            id: icon

            clip: true

            spacing: control.spacing
            display: control.display

            anchors.verticalCenter: parent.verticalCenter

            color: internal.contentColor()

            text: String.fromCodePoint(0xe70d)
            font.family: WinUI3Style.iconFont
            font.pixelSize: 12
        }
    }

    Menu {
        y: control.y + control.height

        id: menu
    }

    background: Rectangle {
        id: gradient
        radius: 4

        implicitHeight: 34
        implicitWidth: 64

        property color backColor: (highlighted) ? (control.WinUI3Style.theme !== WinUI3Style.Theme.Dark) ? WinUI3Style.color(WinUI3Style.Color.Accent) : WinUI3Style.color(WinUI3Style.Color.AccentLight2) : control.WinUI3Style.controlStrokeColorDefault
        property color frontColor: (highlighted) ? (control.WinUI3Style.theme !== WinUI3Style.Theme.Dark) ? WinUI3Style.color(WinUI3Style.Color.AccentDark2) : WinUI3Style.color(WinUI3Style.Color.AccentLight1) : control.WinUI3Style.controlStrokeColorSecondary

        gradient: Gradient {
            GradientStop {
                position: 0
                color: (control.WinUI3Style.theme !== WinUI3Style.Theme.Dark
                        || control.highlighted) ? gradient.backColor : "transparent"
            }
            GradientStop {
                position: 0.8
                color: (control.WinUI3Style.theme !== WinUI3Style.Theme.Dark
                        || control.highlighted) ? gradient.backColor : "transparent"
            }
            GradientStop {
                position: 1
                color: (control.WinUI3Style.theme !== WinUI3Style.Theme.Dark
                        || control.highlighted) ? control.down
                                                  || !control.enabled ? gradient.backColor : gradient.frontColor : "transparent"
            }
        }

        Rectangle {
            id: button

            radius: gradient.radius
            visible: !control.flat || control.down || control.checked
                     || control.highlighted

            x: (control.WinUI3Style.theme === WinUI3Style.Theme.Dark
                && !highlighted) ? parent.x : parent.x + 1
            y: (control.WinUI3Style.theme === WinUI3Style.Theme.Dark
                && !highlighted) ? parent.y : parent.y + 1
            width: (control.WinUI3Style.theme === WinUI3Style.Theme.Dark
                    && !highlighted) ? parent.width : parent.width - 2
            height: (control.WinUI3Style.theme === WinUI3Style.Theme.Dark
                     && !highlighted) ? parent.height : parent.height - 2

            border.width: (control.WinUI3Style.theme === WinUI3Style.Theme.Dark
                           && !highlighted) ? 1 : 0
            border.color: gradient.frontColor
        }
    }

    state: (!enabled) ? "NONE" : (down) ? "PUSHED" : (hovered) ? "HOVERED" : "RELEASED"
    states: [
        State {
            name: "NONE"
            PropertyChanges {
                target: button
                color: (control.highlighted) ? control.WinUI3Style.accentFillColorDisabled : control.WinUI3Style.controlFillColorDisabled
            }
        },
        State {
            name: "RELEASED"
            PropertyChanges {
                target: button
                color: (control.highlighted) ? control.WinUI3Style.accentFillColorPrimary : control.WinUI3Style.controlFillColorDefault
            }
        },
        State {
            name: "PUSHED"
            PropertyChanges {
                target: button
                color: (control.highlighted) ? control.WinUI3Style.accentFillColorTertiary : control.WinUI3Style.controlFillColorTertiary
            }
        },
        State {
            name: "HOVERED"
            PropertyChanges {
                target: button
                color: (control.highlighted) ? control.WinUI3Style.accentFillColorSecondary : control.WinUI3Style.controlFillColorSecondary
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
                return (highlighted) ? control.WinUI3Style.textOnAccentFillColorDisabled : control.WinUI3Style.textFillColorDisabled

            if (control.down)
                return (highlighted) ? control.WinUI3Style.textOnAccentFillColorSecondary : control.WinUI3Style.textFillColorSecondary

            return (highlighted) ? control.WinUI3Style.textOnAccentFillColorPrimary : control.WinUI3Style.textFillColorPrimary
        }
    }
}
