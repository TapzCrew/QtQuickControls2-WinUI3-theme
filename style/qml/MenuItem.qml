import QtQuick 6.3
import QtQuick.Controls.impl 6.3
import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0

T.MenuItem {
    id: control

    leftInset: 4
    rightInset: 4
    bottomInset: 4
    topInset: 4

    topPadding: 9
    bottomPadding: 8
    leftPadding: 12
    rightPadding: 14

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        implicitBackgroundHeight + topInset + bottomInset,
                        implicitContentHeight + topPadding + bottomPadding,
                        implicitIndicatorHeight + topPadding + bottomPadding)

    icon.color: internal.contentColor

    property bool useSystemFocusVisuals: true

    contentItem: Row {
        id: row

        readonly property real arrowPadding: control.subMenu
                                             && control.arrow ? control.arrow.width
                                                                + control.spacing : 0
        readonly property real indicatorPadding: control.checkable
                                                 && control.indicator ? control.indicator.width
                                                                        + control.spacing : 0

        spacing: 14

        IconLabel {
            id: text

            implicitWidth: 34

            rightPadding: control.mirrored ? row.indicatorPadding : row.arrowPadding

            spacing: control.spacing
            mirrored: control.mirrored
            display: control.display

            icon: control.icon
            text: control.text
            font: control.font

            alignment: Qt.AlignLeft | Qt.AlignVCenter

            anchors.verticalCenter: parent.verticalCenter

            color: internal.contentColor
        }

        IconLabel {
            id: shortcut

            leftPadding: !control.mirrored ? row.indicatorPadding : row.arrowPadding

            text: (control.action
                   && control.action.shortcut) ? control.action.shortcut : ""

            color: internal.shortcutColor

            alignment: Qt.AlignRight | Qt.AlignVCenter

            anchors.verticalCenter: parent.verticalCenter

            font.pixelSize: 12
        }
    }

    arrow: IconLabel {
        x: control.mirrored ? control.leftPadding : control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        visible: control.subMenu
        mirrored: control.mirrored
        color: internal.arrowColor

        font.family: WinUI3Style.iconFont
        text: String.fromCodePoint(0xe76c)
    }

    indicator: IconLabel {
        x: control.text ? (control.mirrored ? control.width - width - control.rightPadding : control.leftPadding) : control.leftPadding
                          + (control.availableWidth - width) / 2
        y: control.topPadding + (control.availableHeight - height) / 2

        visible: control.checked
        color: internal.contentColor

        font.family: WinUI3Style.iconFont
        text: (checkable) ? String.fromCodePoint(0xe001) : ""
    }

    background: Rectangle {
        implicitHeight: internal.height
        implicitWidth: internal.width

        radius: 8

        color: internal.backgroundColor
    }

    QtObject {
        id: internal

        readonly property real height: 34
        readonly property real width: 88

        readonly property color backgroundColor: {
            if (!control.enabled)
                return "transparent"

            if (control.down)
                return control.WinUI3Style.subtleFillColorTertiary

            if (control.hovered)
                return control.WinUI3Style.subtleFillColorSecondary

            return "transparent"
        }

        readonly property color arrowColor: {
            if (!control.enabled)
                return control.WinUI3Style.textFillColorDisabled

            if (control.down)
                return control.WinUI3Style.textFillColorTertiary

            return control.WinUI3Style.textFillColorSecondary
        }

        readonly property color contentColor: {
            if (!control.enabled)
                return control.WinUI3Style.textFillColorDisabled

            return control.WinUI3Style.textFillColorPrimary
        }

        readonly property color shortcutColor: {
            if (!control.enabled)
                return control.WinUI3Style.textFillColorDisabled

            return control.WinUI3Style.textFillColorSecondary
        }
    }
}
