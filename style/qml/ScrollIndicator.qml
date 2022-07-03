import QtQuick 6.3

import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0

T.ScrollIndicator {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    contentItem: Rectangle {
        implicitWidth: internal.activeWidth
        implicitHeight: internal.activeWidth

        x: control.width - width - 3

        color: control.WinUI3Style.controlStrongFillColorDefault
        visible: control.size < 1.0
        opacity: 0.0

        states: [
            State {
                name: "active"
                when: control.active
            }
        ]

        transitions: [
            Transition {
                to: "active"
                NumberAnimation {
                    target: control.contentItem
                    property: "opacity"
                    to: 0.0
                }
            },
            Transition {
                from: "active"
                SequentialAnimation {
                    PauseAnimation {
                        duration: 5000
                    }

                    NumberAnimation {
                        target: control.contentItem
                        property: "opacity"
                        to: 0.0
                    }
                }
            }
        ]
    }

    QtObject {
        id: internal

        readonly property real activeWidth: 2
    }
}
