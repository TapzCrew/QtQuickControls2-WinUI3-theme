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
        id: main_layout

        anchors.fill: parent

        Label {
            text: "CheckBox"
            font.pixelSize: 28
            font.family: "Segoe UI Semibold"
        }

        ScrollView {
            id: scroll_view

            contentWidth: availableWidth

            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true

            clip: true

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            Flickable {
                anchors.fill: parent

                contentWidth: contentItem.childrenRect.width
                contentHeight: contentItem.childrenRect.height

                boundsBehavior: Flickable.StopAtBounds

                ColumnLayout {
                    spacing: 16

                    width: Math.max(scroll_view.implicitWidth,
                                    scroll_view.availableWidth)

                    Label {
                        text: "CheckBox presents an option button that can be toggled on or off. "
                              + "Check boxes are typically used to select one or more options from a set of options."

                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        wrapMode: Text.WordWrap
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "A 2-state CheckBox."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        Pane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                CheckBox {
                                    text: "Two-state Checkbox"
                                    checked: false

                                    onCheckedChanged: label_checkbox_1.text
                                                      = "Output:\nYou ".concat(
                                                          (checked) ? "checked" : "unchecked",
                                                          " the box")
                                }

                                CheckBox {
                                    text: "Two-state Disabled Checkbox"
                                    checked: true
                                    enabled: false
                                }

                                Label {
                                    id: label_checkbox_1
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
                            text: "A 3-state CheckBox."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        Pane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Column {
                                    ButtonGroup {
                                        id: check_box_group

                                        exclusive: false

                                        checkState: parent_box.checkState
                                    }

                                    CheckBox {
                                        id: parent_box

                                        text: "Select all"
                                        checked: true

                                        checkState: check_box_group.checkState
                                    }

                                    CheckBox {
                                        text: "Option 1"

                                        leftPadding: indicator.width

                                        ButtonGroup.group: check_box_group
                                    }

                                    CheckBox {
                                        text: "Option 2"

                                        leftPadding: indicator.width

                                        ButtonGroup.group: check_box_group
                                    }

                                    CheckBox {
                                        text: "Option 3"

                                        leftPadding: indicator.width

                                        ButtonGroup.group: check_box_group
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
