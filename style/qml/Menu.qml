import QtQuick 6.3
import QtQuick.Window 6.3
import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0
import WinUI3Style.Impl 1.0

T.Menu {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    overlap: 1

    delegate: MenuItem {}

    contentItem: ListView {
        id: listView

        implicitHeight: contentHeight
        implicitWidth: contentWidth

        clip: true

        model: control.contentModel

        interactive: Window.window ? contentHeight + control.topPadding
                                     + control.bottomPadding > Window.window.height : false

        currentIndex: control.currentIndex

        ScrollIndicator.vertical: ScrollIndicator {}
    }

    background: Rectangle {
        implicitHeight: internal.height
        implicitWidth: {
            var result = internal.width
            var padding = 0
            for (var i = 0; i < count; ++i) {
                let item = itemAt(i)

                result = Math.max(item.contentItem.implicitWidth + 12 + 14,
                                  result)
                padding = Math.max(item.padding, padding)
            }
            return result + padding * 2
        }

        radius: 8

        color: control.WinUI3Style.solidBackgroundFillColorBase

        border.color: control.WinUI3Style.surfaceStrokeColorFlyOut
        border.width: 1
    }

    // TODO animation
    T.Overlay.modal: Rectangle {
        radius: 8

        color: "transparent"
    }

    T.Overlay.modeless: Rectangle {
        radius: 8

        color: "transparent"
    }

    QtObject {
        id: internal

        readonly property real height: 34
        readonly property real width: 88
    }
}
