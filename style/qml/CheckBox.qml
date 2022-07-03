import QtQuick 6.3
import QtQuick.Controls.impl 6.3

import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0

T.CheckBox {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        implicitBackgroundHeight + topInset + bottomInset,
                        implicitContentHeight + topPadding + bottomPadding,
                        implicitIndicatorHeight + topPadding + bottomPadding)

    padding: 6
    spacing: 8

    property bool useSystemFocusVisuals: true

    indicator: Rectangle {
        implicitWidth: 20
        implicitHeight: 20

        x: control.text ? (control.mirrored ? control.width - width - control.rightPadding : control.leftPadding) : control.leftPadding
                          + (control.availableWidth - width) / 2
        y: control.topPadding + (control.availableHeight - height) / 2

        radius: 4

        color: internal.backgroundColor()
        border.color: internal.borderColor()
        border.width: 1

        IconLabel {
            anchors.fill: parent

            clip: true

            spacing: control.spacing
            mirrored: control.mirrored
            display: control.display

            icon: control.icon
            font.family: WinUI3Style.iconFont
            font.weight: 600
            text: {
                if (control.checkState === Qt.Checked)
                    return String.fromCodePoint(0xe73e)
                else if (control.checkState === Qt.PartiallyChecked)
                    return String.fromCodePoint(0xe73c)

                return ""
            }

            color: internal.checkMarkColor()

            visible: control.checkState == Qt.Checked
                     || control.checkState == Qt.PartiallyChecked
        }
    }

    contentItem: Text {
        leftPadding: control.indicator
                     && !control.mirrored ? control.indicator.width + control.spacing : 0
        rightPadding: control.indicator
                      && control.mirrored ? control.indicator.width + control.spacing : 0

        text: control.text
        font: control.font
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter

        color: internal.contentColor()
    }

    QtObject {
        id: internal

        function checkMarkColor() {
            if (!control.enabled)
                return control.WinUI3Style.textOnAccentFillColorDisabled

            if (control.down)
                return control.WinUI3Style.textOnAccentFillColorSecondary

            return control.WinUI3Style.textOnAccentFillColorPrimary
        }

        function contentColor() {
            if (!control.enabled)
                return control.WinUI3Style.textFillColorDisabled

            return control.WinUI3Style.textFillColorPrimary
        }

        function backgroundColor() {
            if (control.checkState == Qt.Checked
                    || control.checkState == Qt.PartiallyChecked) {
                if (!control.enabled)
                    return control.WinUI3Style.accentFillColorDisabled

                if (control.hovered)
                    return control.WinUI3Style.accentFillColorSecondary

                if (control.down)
                    return control.WinUI3Style.accentFillColorTertiary

                return control.WinUI3Style.accentFillColorPrimary
            }

            if (!control.enabled)
                return control.WinUI3Style.controlAltFillColorDisabled

            if (control.hovered)
                return control.WinUI3Style.controlAltFillColorTertiary

            if (control.down)
                return control.WinUI3Style.controlAltFillColorQuarternary

            return control.WinUI3Style.controlAltFillColorSecondary
        }

        function borderColor() {
            if (control.checkState == Qt.Checked
                    || control.checkState == Qt.PartiallyChecked) {
                if (!control.enabled)
                    return control.WinUI3Style.accentFillColorDisabled

                if (control.hovered)
                    return control.WinUI3Style.accentFillColorSecondary

                if (control.down)
                    return control.WinUI3Style.accentFillColorTertiary

                return control.WinUI3Style.accentFillColorPrimary
            }

            if (!control.enabled || control.down)
                return control.WinUI3Style.controlStrongStrokeColorDisabled

            return control.WinUI3Style.controlStrongStrokeColorDefault
        }
    }
}
