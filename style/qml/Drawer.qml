import QtQuick 6.3
import QtQuick.Templates 6.3 as T
import QtQuick.Controls.impl 6.3

import WinUI3Style 1.0

T.Drawer {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    padding: 8

    enter: Transition {
        SmoothedAnimation {
            velocity: 5
        }
    }
    exit: Transition {
        SmoothedAnimation {
            velocity: 5
        }
    }

    background: Rectangle {
        color: (!interactive && !modal
                && visible) ? "transparent" : control.WinUI3Style.systemFillColorSolidNeutralBackground
    }
}
