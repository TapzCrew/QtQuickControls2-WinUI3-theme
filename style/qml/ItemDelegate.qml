import QtQuick 6.3
import QtQuick.Templates 6.3 as T
import QtQuick.Controls.impl 6.3

import WinUI3Style 1.0

T.ItemDelegate {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        implicitBackgroundHeight + topInset + bottomInset,
                        implicitContentHeight + topPadding + bottomPadding,
                        implicitIndicatorHeight + topPadding + bottomPadding)

    padding: 8
    spacing: 16

    leftPadding: 10

    icon.width: 20
    icon.height: 20

    icon.color: internal.contentColor()

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display
        alignment: control.display === IconLabel.IconOnly
                   || control.display === IconLabel.TextUnderIcon ? Qt.AlignCenter : Qt.AlignLeft

        icon: control.icon
        text: control.text
        font: control.font
        color: internal.contentColor()
    }

    background: Rectangle {
        id: background
        implicitWidth: 300
        implicitHeight: 36

        color: (control.hovered
                || control.highlighted) ? (control.down) ? control.WinUI3Style.subtleFillColorTertiary : control.WinUI3Style.subtleFillColorSecondary : control.WinUI3Style.subtleFillColorTransparent

        Rectangle {
            visible: control.highlighted

            anchors.left: background.left

            y: (control.pressed) ? 13 : 10

            width: 3
            height: (control.pressed) ? 10 : 16

            color: control.WinUI3Style.accentFillColorPrimary

            radius: 8

            Behavior on height {
                NumberAnimation {
                    duration: 25
                }
            }

            Behavior on y {
                NumberAnimation {
                    duration: 25
                }
            }
        }

        radius: 4
    }

    QtObject {
        id: internal

        function contentColor() {
            if (control.down)
                return control.WinUI3Style.textFillColorSecondary
            if (control.disabled)
                return control.WinUI3Style.textFillColorDisabled
            return control.WinUI3Style.textFillColorPrimary
        }
    }
}
