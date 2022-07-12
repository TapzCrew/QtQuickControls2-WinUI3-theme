import QtQuick 6.3
import QtQuick.Controls.impl 6.3

import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0
import WinUI3Style.Impl 1.0

T.ScrollBar {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    policy: T.ScrollBar.AsNeeded
    visible: control.policy !== T.ScrollBar.AlwaysOff
    minimumSize: orientation === Qt.Horizontal ? height / width : width / height

    topPadding: internal.arrowHeight
    bottomPadding: internal.arrowHeight
    leftPadding: internal.idleLeftPadding
    rightPadding: internal.idleRightPadding

    property bool useSystemFocusVisuals: true

    Item {
        implicitWidth: internal.backgroundWidth
        implicitHeight: internal.arrowHeight

        Triangle {
            id: up_arrow

            orientation: Triangle.Orientation.Up

            anchors.fill: parent

            triangleWidth: (up_ma.pressed) ? 7 : 8
            triangleHeight: (up_ma.pressed) ? 5 : 6

            fill: true
            stroke: false

            fillColor: {
                if (up_ma.containsMouse)
                    return control.WinUI3Style.textFillColorSecondary

                return control.WinUI3Style.controlStrongFillColorDefault
            }

            visible: parent.visible && control.size < 1.0
            opacity: 0.0
        }

        MouseArea {
            id: up_ma

            anchors.fill: parent

            hoverEnabled: true

            onPressed: control.decrease()
        }
    }

    Item {
        implicitWidth: internal.backgroundWidth
        implicitHeight: internal.arrowHeight

        y: parent.height - height

        Triangle {
            id: down_arrow

            orientation: Triangle.Orientation.Down

            anchors.fill: parent

            triangleWidth: (down_ma.pressed) ? 7 : 8
            triangleHeight: (down_ma.pressed) ? 5 : 6

            fill: true
            stroke: false

            fillColor: {
                if (down_ma.containsMouse)
                    return control.WinUI3Style.textFillColorSecondary

                return control.WinUI3Style.controlStrongFillColorDefault
            }

            visible: parent.visible && control.size < 1.0
            opacity: 0.0
        }

        MouseArea {
            id: down_ma

            anchors.fill: parent

            hoverEnabled: true

            onPressed: control.increase()
        }
    }

    contentItem: Rectangle {
        radius: 6

        visible: parent.visible && control.size < 1.0

        color: control.WinUI3Style.controlStrongFillColorDefault
    }

    background: Rectangle {
        implicitWidth: internal.backgroundWidth
        implicitHeight: internal.backgroundWidth

        color: "#3B555555"

        radius: 6

        visible: control.size < 1.0

        opacity: 0.0
    }

    states: [
        State {
            name: "idle"
            when: !control.hovered
        },

        State {
            name: "hovered"
            when: control.hovered
        }
    ]

    transitions: [
        Transition {
            to: "idle"

            SequentialAnimation {
                PauseAnimation {
                    duration: 500
                }

                ParallelAnimation {
                    NumberAnimation {
                        targets: [control]
                        property: "leftPadding"
                        to: internal.idleLeftPadding
                        duration: internal.animationDuration
                    }
                    NumberAnimation {
                        targets: [control]
                        property: "rightPadding"
                        to: internal.idleRightPadding
                        duration: internal.animationDuration
                    }
                    NumberAnimation {
                        targets: [control.background, up_arrow, down_arrow]
                        property: "opacity"
                        to: 0.0
                        duration: internal.animationDuration
                    }
                }
            }
        },
        Transition {
            to: "hovered"

            SequentialAnimation {
                PauseAnimation {
                    duration: 500
                }
                ParallelAnimation {
                    NumberAnimation {
                        targets: [control]
                        property: "leftPadding"
                        to: internal.hoveredLeftPadding
                        duration: internal.animationDuration
                    }
                    NumberAnimation {
                        targets: [control]
                        property: "rightPadding"
                        to: internal.hoveredRightPadding
                        duration: internal.animationDuration
                    }
                    NumberAnimation {
                        targets: [control.background, up_arrow, down_arrow]
                        property: "opacity"
                        to: 1.0
                        duration: internal.animationDuration
                    }
                }
            }
        }
    ]

    QtObject {
        id: internal

        readonly property real idleWidth: 2

        readonly property real idleLeftPadding: backgroundWidth - idleWidth - 3
        readonly property real idleRightPadding: 3

        readonly property real hoveredWidth: 6

        readonly property real hoveredLeftPadding: backgroundWidth - hoveredWidth - 3
        readonly property real hoveredRightPadding: 3

        readonly property real backgroundWidth: 12
        readonly property real arrowHeight: 14

        readonly property int animationDuration: 100
    }
}
