import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0

T.Slider {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitHandleWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitHandleHeight + topPadding + bottomPadding)

    padding: 6

    property bool useSystemFocusVisuals: true

    handle: Rectangle {
        id: border

        implicitWidth: 22
        implicitHeight: 22

        x: control.leftPadding + (control.horizontal ? control.visualPosition * (control.availableWidth - width) : (control.availableWidth - width) / 2)
        y: control.topPadding
           + (control.horizontal ? (control.availableHeight - height) / 2 : control.visualPosition
                                   * (control.availableHeight - height))

        radius: 11

        property color backColor: control.WinUI3Style.controlStrokeColorDefault
        property color frontColor: control.WinUI3Style.controlStrokeColorSecondary

        gradient: Gradient {
            GradientStop {
                position: 0
                color: border.backColor
            }
            GradientStop {
                position: 0.8
                color: border.backColor
            }
            GradientStop {
                position: 1
                color: border.frontColor
            }
        }

        Rectangle {
            implicitWidth: 20
            implicitHeight: 20

            anchors.centerIn: parent
            radius: 10

            color: control.WinUI3Style.controlSolidFillColorDefault

            Rectangle {
                anchors.centerIn: parent

                implicitWidth: internal.innerCircleWidth
                implicitHeight: internal.innerCircleHeight

                radius: internal.innerCircleRadius

                color: internal.innerCircleColor()
            }
        }
    }

    background: Item {
        implicitWidth: control.horizontal ? 200 : 4
        implicitHeight: control.horizontal ? 4 : 200

        x: control.leftPadding + (control.horizontal ? 0 : (control.availableWidth - width) / 2)
        y: control.topPadding + (control.horizontal ? (control.availableHeight - height) / 2 : 0)
        width: control.horizontal ? control.availableWidth : implicitWidth
        height: control.horizontal ? implicitHeight : control.availableHeight

        scale: control.horizontal && control.mirrored ? -1 : 1

        Rectangle {
            x: control.horizontal ? 0 : (parent.width - width) / 2
            y: control.horizontal ? (parent.height - height) / 2 : 0
            width: control.horizontal ? parent.width : 4
            height: !control.horizontal ? parent.height : 4

            radius: 4
            color: (control.enabled) ? control.WinUI3Style.controlStrongFillColorDefault : control.WinUI3Style.controlStrongFillColorDisabled
        }

        Rectangle {
            x: control.horizontal ? 0 : (parent.width - width) / 2
            y: control.horizontal ? (parent.height - height)
                                    / 2 : control.visualPosition * parent.height
            width: control.horizontal ? control.position * parent.width : 4
            height: !control.horizontal ? control.position * parent.height : 4
            radius: 4

            color: (control.enabled) ? control.WinUI3Style.accentFillColorPrimary : control.WinUI3Style.accentFillColorDisabled
        }
    }

    states: [
        State {
            name: "idle"
            when: !control.hovered
        },
        State {
            name: "hovered"
            when: control.hovered && !control.pressed
        },
        State {
            name: "pushed"
            when: control.pressed
        }
    ]

    transitions: [
        Transition {
            to: "idle"

            NumberAnimation {
                targets: [internal]
                property: "innerCircleWidth"

                to: internal.innerCircleIdleDiameter

                duration: internal.innerCircleDuration

                easing.type: Easing.OutQuad
            }

            NumberAnimation {
                targets: [internal]
                property: "innerCircleHeight"

                to: internal.innerCircleIdleDiameter

                duration: internal.innerCircleDuration

                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                targets: [internal]
                property: "innerCircleRadius"

                to: internal.innerCircleIdleDiameter / 2

                duration: internal.innerCircleDuration

                easing.type: Easing.OutQuad
            }
        },
        Transition {
            to: "hovered"

            NumberAnimation {
                targets: [internal]
                property: "innerCircleWidth"

                to: internal.innerCircleHoveredDiameter

                duration: internal.innerCircleDuration

                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                targets: [internal]
                property: "innerCircleHeight"

                to: internal.innerCircleHoveredDiameter

                duration: internal.innerCircleDuration

                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                targets: [internal]
                property: "innerCircleRadius"

                to: internal.innerCircleHoveredDiameter / 2

                duration: internal.innerCircleDuration

                easing.type: Easing.OutQuad
            }
        },
        Transition {
            to: "pushed"

            NumberAnimation {
                targets: [internal]
                property: "innerCircleWidth"

                to: internal.innerCirclePushedDiameter

                duration: internal.innerCircleDuration

                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                targets: [internal]
                property: "innerCircleHeight"

                to: internal.innerCirclePushedDiameter

                duration: internal.innerCircleDuration

                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                targets: [internal]
                property: "innerCircleRadius"

                to: internal.innerCirclePushedDiameter / 2

                duration: internal.innerCircleDuration

                easing.type: Easing.OutQuad
            }
        }
    ]

    QtObject {
        id: internal

        readonly property real innerCircleIdleDiameter: 10
        readonly property real innerCircleHoveredDiameter: 14
        readonly property real innerCirclePushedDiameter: 8

        readonly property real innerCircleDuration: 150

        property real innerCircleWidth: innerCircleIdleDiameter
        property real innerCircleHeight: innerCircleIdleDiameter
        property real innerCircleRadius: innerCircleIdleDiameter / 2

        function innerCircleColor() {
            if (control.hovered)
                return control.WinUI3Style.accentFillColorSecondary

            if (control.pressed)
                return control.WinUI3Style.accentFillColorDisabled

            if (control.hovered)
                return control.WinUI3Style.accentFillColorTertiary

            return control.WinUI3Style.accentFillColorPrimary
        }
    }
}
