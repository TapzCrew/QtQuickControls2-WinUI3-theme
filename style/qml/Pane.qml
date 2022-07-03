import QtQuick 6.3
import QtQuick.Templates 6.3 as T
import QtQuick.Controls.impl 6.3

import WinUI3Style 1.0

T.Pane {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    topPadding: 16
    leftPadding: 12
    rightPadding: 12
    bottomPadding: 16

    background: Rectangle {
        color: control.WinUI3Style.layerFillColorDefault

        border.width: 1
        border.color: control.WinUI3Style.cardStrokeColorDefault

        radius: 4
    }
}
