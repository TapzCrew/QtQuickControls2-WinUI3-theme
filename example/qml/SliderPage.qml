import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

import WinUI3Style 1.0

Frame {
    id: root

    topPadding: 32
    leftPadding: 32
    rightPadding: 0
    bottomPadding: 0

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: "Slider"
            font.pixelSize: 28
            font.family: "Segoe UI Semibold"
        }

        ScrollView {
            id: scroll_view

            contentWidth: availableWidth

            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            Flickable {
                anchors.fill: parent

                clip: true

                contentWidth: contentItem.childrenRect.width
                contentHeight: contentItem.childrenRect.height

                boundsBehavior: Flickable.StopAtBounds

                ColumnLayout {
                    spacing: 16

                    width: Math.max(scroll_view.implicitWidth,
                                    scroll_view.availableWidth)

                    Label {
                        text: "Use a Slider when you want your users to be able to set defined, contiguous values (such as volume or brightness) or a range of discrete values (such as screen resolution settings)"

                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        wrapMode: Text.WordWrap
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "A simple Slider"

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        Pane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Slider {
                                    id: slider1

                                    stepSize: 1
                                    from: 0
                                    to: 100

                                    onValueChanged: label_slider_1.text = "Output:\n".concat(
                                                        value)
                                }

                                Label {
                                    id: label_slider_1
                                    text: "Output:"

                                    Layout.alignment: Qt.AlignRight
                                }
                            }
                        }
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "A Slider with range and steps specified."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        Pane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Slider {
                                    id: slider2

                                    stepSize: 1
                                    from: 500
                                    to: 1000

                                    onValueChanged: label_slider_2.text = "Output:\n".concat(
                                                        value)
                                }

                                Label {
                                    id: label_slider_2
                                    text: "Output:"

                                    Layout.alignment: Qt.AlignRight
                                }
                            }
                        }
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "A vertical Slider with range specified."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        Pane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Slider {
                                    id: slider4

                                    onValueChanged: label_slider_4.text = "Output:\n".concat(
                                                        value)

                                    stepSize: 1
                                    from: -50
                                    to: 50

                                    value: 0

                                    orientation: Qt.Vertical
                                }

                                Label {
                                    id: label_slider_4
                                    text: "Output:"

                                    Layout.alignment: Qt.AlignRight
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
