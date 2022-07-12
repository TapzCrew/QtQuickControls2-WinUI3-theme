import QtQuick 6.3
import QtQuick.Controls.impl 6.3

import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0
import WinUI3Style.Impl 1.0

T.Button {
    id: control

    rightPadding: 12
    leftPadding: 12
    topPadding: 6
    bottomPadding: 6
    spacing: 8

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    icon.color: internal.contentColor

    property bool useSystemFocusVisuals: true

    contentItem: IconLabel {
        clip: true

        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font

        color: internal.contentColor
    }

    background: Rectangle {
        id: gradient
        radius: 4

        implicitHeight: 34
        implicitWidth: 64

        gradient: Gradient {
            GradientStop {
                position: 0
                color: internal.backColor
            }
            GradientStop {
                position: 0.8
                color: internal.backColor
            }
            GradientStop {
                position: 1
                color: internal.frontColor
            }
        }

        Rectangle {
            id: button

            radius: gradient.radius
            visible: !control.flat || control.down || control.checked
                     || control.highlighted

            x: parent.x + border.width
            y: parent.y + border.width

            width: parent.width - border.width * 2
            height: parent.height - border.width * 2

            color: internal.backgroundColorReleased

            border.width: ((highlighted || checked) && down) ? 0 : 1
            border.color: internal.borderColor
        }
    }

    states: [
        State {
            name: "disabled"
            when: !control.enabled
        },
        State {
            name: "idle"
            when: control.enabled && !control.down && !control.hovered
        },
        State {
            name: "pushed"
            when: control.down
        },
        State {
            name: "hovered"
            when: control.hovered
        }
    ]

    transitions: [
        Transition {
            to: "disabled"

            ColorAnimation {
                target: button
                property: "color"

                to: (checked) ? control.WinUI3Style.controlFillColorDisabled : internal.backgroundColorDisabled

                duration: internal.colorTransitionsDuration

                easing.type: Easing.OutQuad
            }
        },
        Transition {
            to: "idle"

            ColorAnimation {
                target: button
                property: "color"

                to: internal.backgroundColorReleased

                duration: internal.colorTransitionsDuration

                easing.type: Easing.OutQuad
            }
        },
        Transition {
            to: "pushed"

            ColorAnimation {
                target: button
                property: "color"

                to: internal.backgroundColorPushed

                duration: internal.colorTransitionsDuration

                easing.type: Easing.OutQuad
            }
        },
        Transition {
            to: "hovered"

            ColorAnimation {
                target: button
                property: "color"

                to: internal.backgroundColorHovered

                duration: internal.colorTransitionsDuration

                easing.type: Easing.OutQuad
            }
        }
    ]

    QtObject {
        id: internal

        readonly property color backgroundColorDisabled: (control.highlighted
                                                          || checked) ? control.WinUI3Style.accentFillColorDisabled : control.WinUI3Style.controlFillColorDisabled
        readonly property color backgroundColorReleased: (control.highlighted
                                                          || control.checked) ? control.WinUI3Style.accentFillColorPrimary : control.WinUI3Style.controlFillColorDefault
        readonly property color backgroundColorPushed: (control.highlighted
                                                        || control.checked) ? control.WinUI3Style.accentFillColorTertiary : control.WinUI3Style.controlFillColorTertiary
        readonly property color backgroundColorHovered: (control.highlighted
                                                         || control.checked) ? control.WinUI3Style.accentFillColorSecondary : control.WinUI3Style.controlFillColorSecondary

        readonly property color borderColor: (control.highlighted
                                              || control.checked) ? (!control.enabled) ? "transparent" : control.WinUI3Style.accentFillColorPrimary : ((control.WinUI3Style.theme === WinUI3Style.Theme.Light && !down && !(highlighted || checked)) || !control.enabled) ? "transparent" : control.WinUI3Style.controlStrokeColorDefault

        readonly property int colorTransitionsDuration: 100

        readonly property color backColor: {
            if (control.WinUI3Style.theme === WinUI3Style.Theme.Dark
                    && !highlighted && !checked)
                return "transparent"

            if (!enabled || down)
                return "transparent"

            if (highlighted || checked)
                return control.WinUI3Style.accentFillColorPrimary

            return control.WinUI3Style.controlStrokeColorDefault
        }

        readonly property color frontColor: {
            if (control.WinUI3Style.theme === WinUI3Style.Theme.Dark
                    && !highlighted && !checked)
                return "transparent"

            if (!enabled || down)
                return "transparent"

            if (highlighted || checked) {
                if (control.WinUI3Style.theme !== WinUI3Style.Theme.Dark)
                    return WinUI3Style.color(WinUI3Style.Color.AccentDark2)
                else
                    WinUI3Style.color(WinUI3Style.Color.AccentLight1)
            }

            return control.WinUI3Style.controlStrokeColorSecondary
        }

        readonly property color contentColor: {
            if (!control.enabled)
                return (control.highlighted
                        || control.checked) ? control.WinUI3Style.textOnAccentFillColorDisabled : control.WinUI3Style.textFillColorDisabled

            if (control.down)
                return (control.highlighted)
                        || control.checked ? control.WinUI3Style.textOnAccentFillColorSecondary : control.WinUI3Style.textFillColorSecondary

            return (control.highlighted
                    || control.checked) ? control.WinUI3Style.textOnAccentFillColorPrimary : control.WinUI3Style.textFillColorPrimary
        }
    }
}
