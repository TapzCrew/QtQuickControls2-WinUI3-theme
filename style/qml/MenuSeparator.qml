import QtQuick
import QtQuick.Templates as T

import WinUI3Style 1.0

T.MenuSeparator {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    contentItem: Rectangle {
        implicitWidth: 88
        implicitHeight: 1
        color: control.WinUI3Style.dividerStrokeColorDefault
    }

    background: Rectangle {
        color: "transparent"
    }
}
