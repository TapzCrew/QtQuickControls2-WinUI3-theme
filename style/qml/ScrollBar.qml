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

    Triangle {
        id: up_arrow

        orientation: Triangle.Orientation.Up

        implicitWidth: internal.backgroundWidth
        implicitHeight: internal.arrowHeight

        triangleWidth: 8
        triangleHeight: 6

        fill: true
        stroke: false

        fillColor: (up_ma.hovered) ? control.WinUI3Style.controlStrongFillColorDefault : control.WinUI3Style.textFillColorSecondary

        visible: parent.visible && control.size < 1.0
        opacity: 0.0

        MouseArea {
            id: up_ma

            anchors.fill: parent
        }
    }

    Triangle {
        id: down_arrow

        orientation: Triangle.Orientation.Down

        implicitWidth: internal.backgroundWidth
        implicitHeight: internal.arrowHeight

        triangleWidth: 8
        triangleHeight: 6

        y: parent.height - height

        fill: true
        stroke: false

        fillColor: (down_ma.hovered) ? control.WinUI3Style.controlStrongFillColorDefault : control.WinUI3Style.textFillColorSecondary

        visible: parent.visible && control.size < 1.0
        opacity: 0.0

        MouseArea {
            id: down_ma

            anchors.fill: parent
        }
    }

    contentItem: Rectangle {
        implicitWidth: internal.idleWidth
        implicitHeight: internal.idleWidth

        x: control.width - width - 3

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
                    SmoothedAnimation {
                        targets: [control.contentItem]
                        property: "width"
                        from: internal.hoveredWidth
                        to: internal.idleWidth
                        velocity: 50
                    }
                    SmoothedAnimation {
                        targets: [control.background, up_arrow, down_arrow]
                        property: "opacity"
                        to: 0.0
                        duration: 100
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
                    SmoothedAnimation {
                        targets: [control.contentItem]
                        property: "width"
                        to: internal.hoveredWidth
                        velocity: 50
                    }
                    SmoothedAnimation {
                        targets: [control.background, up_arrow, down_arrow]
                        property: "opacity"
                        to: 1.0
                        duration: 100
                    }
                }
            }
        }
    ]

    QtObject {
        id: internal

        readonly property real idleWidth: 2
        readonly property real hoveredWidth: 6
        readonly property real backgroundWidth: 12
        readonly property real arrowHeight: 14
    }
}
