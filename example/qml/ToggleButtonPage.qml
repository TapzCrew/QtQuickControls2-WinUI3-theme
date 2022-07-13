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
            text: "ToggleButton"
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
                        text: "A ToggleButton looks like a Button, but works like a CheckBox. It has two states, checked (on) or unchecked (off). You can determine it's state by checking the checked property."

                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        wrapMode: Text.WordWrap
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "A simple ToggleButton with text content."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Button {
                                    id: button

                                    text: "ToggleButton"

                                    checkable: true

                                    Layout.alignment: Qt.AlignVCenter

                                    enabled: !checkbox.checked
                                }

                                Item {
                                    Layout.fillWidth: true
                                }

                                Label {
                                    id: label_btn_1
                                    text: (button.checked) ? "Output:\nOn" : "Output:\nOff"

                                    Layout.alignment: Qt.AlignRight
                                }

                                Frame {
                                    Layout.fillHeight: true
                                    Layout.alignment: Qt.AlignRight

                                    CheckBox {
                                        id: checkbox

                                        text: "Disable ToggleButton"

                                        checked: false
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
