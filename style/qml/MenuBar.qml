import QtQuick 6.3
import QtQuick.Templates 6.3 as T
import QtQuick.Controls.impl 6.3

import WinUI3Style 1.0

T.MenuBar {
    id: control

    padding: 3

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    spacing: 4

    delegate: MenuBarItem {}

    contentItem: Row {
        spacing: control.spacing
        Repeater {
            model: control.contentModel
        }
    }

    background: Rectangle {
        implicitHeight: 38
        color: "transparent"
    }
}
