import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

import WinUI3Style 1.0

import "." as App

Frame {
    id: root

    topPadding: 32
    leftPadding: 32
    rightPadding: 0
    bottomPadding: 0

    property var push
    ColumnLayout {
        id: main_layout

        anchors.fill: parent

        Label {
            text: "Button"
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

                contentWidth: contentItem.childrenRect.width
                contentHeight: contentItem.childrenRect.height

                boundsBehavior: Flickable.StopAtBounds

                clip: true

                ColumnLayout {
                    spacing: 16

                    width: Math.max(scroll_view.implicitWidth,
                                    scroll_view.availableWidth)

                    Label {
                        text: "Button presents a push-button that can be pushed or clicked by the user." + " Buttons are normally used to perform an action, or to answer a question."

                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        wrapMode: Text.WordWrap
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "A simple Button with text content."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Button {
                                    text: "Button 1"

                                    Layout.alignment: Qt.AlignVCenter

                                    onClicked: label_btn_1.text = "Output:\nYou clicked: Button1"
                                }

                                Label {
                                    id: label_btn_1
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
                            text: "A disabled Button with text content."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Button {
                                    text: "Button 2"

                                    enabled: false

                                    Layout.alignment: Qt.AlignVCenter
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "A Highlighted Button with text content."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Button {
                                    text: "Button 3"
                                    highlighted: true

                                    Layout.alignment: Qt.AlignVCenter

                                    onClicked: label_btn_2.text = "Output:\nYou clicked: Button3"
                                }

                                Label {
                                    id: label_btn_2
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
