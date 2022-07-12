import QtQuick 6.3
import QtQuick.Templates 6.3 as T

T.StackView {
    id: control

    popEnter: Transition {
        ParallelAnimation {
            NumberAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: internal.opacityTransitionDuration
                easing.type: Easing.InQuint
            }
            NumberAnimation {
                property: "x"
                from: (control.mirrored ? -0.3 : 0.3) * -control.width
                to: 0
                duration: internal.xTransitionDuration
                easing.type: Easing.OutCubic
            }
        }
    }

    popExit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: internal.opacityTransitionDuration
            easing.type: Easing.OutQuint
        }
    }

    pushEnter: Transition {
        ParallelAnimation {
            NumberAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: internal.opacityTransitionDuration
                easing.type: Easing.InQuint
            }
            NumberAnimation {
                property: "x"
                from: (control.mirrored ? -0.3 : 0.3) * control.width
                to: 0
                duration: internal.xTransitionDuration
                easing.type: Easing.OutCubic
            }
        }
    }

    pushExit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: internal.opacityTransitionDuration
            easing.type: Easing.OutQuint
        }
    }

    replaceEnter: Transition {
        ParallelAnimation {
            NumberAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: internal.opacityTransitionDuration
                easing.type: Easing.InQuint
            }
            NumberAnimation {
                property: "x"
                from: (control.mirrored ? -0.3 : 0.3) * control.width
                to: 0
                duration: internal.xTransitionDuration
                easing.type: Easing.OutCubic
            }
        }
    }

    replaceExit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: internal.opacityTransitionDuration
            easing.type: Easing.OutQuint
        }
    }

    QtObject {
        id: internal

        readonly property int opacityTransitionDuration: 200
        readonly property int xTransitionDuration: 400
    }
}
