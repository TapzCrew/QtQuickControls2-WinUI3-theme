import QtQuick 6.3
import QtQuick.Templates 6.3 as T
import QtQuick.Controls.impl 6.3

import WinUI3Style 1.0

T.MenuBarItem {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        implicitBackgroundHeight + topInset + bottomInset,
                        implicitContentHeight + topPadding + bottomPadding,
                        implicitIndicatorHeight + topPadding + bottomPadding)

    topPadding: 6
    bottomPadding: 6
    leftPadding: 10
    rightPadding: 10
    spacing: 11

    icon.width: 20
    icon.height: 20
    icon.color: internal.contentColor

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display
        alignment: Qt.AlignLeft

        icon: control.icon
        text: control.text
        font: control.font
        color: internal.contentColor
    }

    background: Rectangle {
        implicitHeight: 32

        radius: 4

        color: internal.backgroundColor
    }

    QtObject {
        id: internal

        readonly property color contentColor: {
            if (!control.enabled)
                return control.WinUI3Style.textFillColorDisabled

            if (control.down)
                return control.WinUI3Style.textFillColorSecondary

            return control.WinUI3Style.textFillColorPrimary
        }

        readonly property color backgroundColor: {
            if (!control.enabled)
                return control.WinUI3Style.subtleFillColorDisabled

            if (control.down)
                return control.WinUI3Style.subtleFillColorTertiary

            if (control.hovered)
                return control.WinUI3Style.subtleFillColorSecondary

            return control.WinUI3Style.subtleFillColorTransparent
        }
    }
}
