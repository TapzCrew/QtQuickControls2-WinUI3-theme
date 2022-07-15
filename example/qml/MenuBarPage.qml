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
            text: "Menu"
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
                        text: "The Menubar simplifies the creation of basic applications by providing a set of menus at the top of the app or window"

                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        wrapMode: Text.WordWrap
                    }

                    Label {
                        text: "from QtQuick.Controls"

                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        wrapMode: Text.WordWrap

                        font.pixelSize: 12
                        font.family: "Segoe UI Light"
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "A simple MenuBar"

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            ColumnLayout {
                                anchors.fill: parent

                                Label {
                                    id: label1

                                    Layout.preferredHeight: menuBar1.height

                                    Layout.alignment: Qt.AlignVCenter
                                    Layout.fillWidth: true
                                }

                                MenuBar {
                                    id: menuBar1

                                    Layout.fillWidth: true

                                    Menu {
                                        title: "File"

                                        Action {
                                            text: "New"

                                            onTriggered: label1.text = "You clicked: " + text
                                        }
                                        Action {
                                            text: "Open"

                                            onTriggered: label1.text = "You clicked: " + text
                                        }
                                        Action {
                                            text: "Save"

                                            onTriggered: label1.text = "You clicked: " + text
                                        }
                                        Action {
                                            text: "Exit"

                                            onTriggered: label1.text = "You clicked: " + text
                                        }
                                    }

                                    Menu {
                                        title: "Edit"

                                        Action {
                                            text: "Undo"

                                            onTriggered: label1.text = "You clicked: " + text
                                        }
                                        Action {
                                            text: "Cut"

                                            onTriggered: label1.text = "You clicked: " + text
                                        }
                                        Action {
                                            text: "Copy"

                                            onTriggered: label1.text = "You clicked: " + text
                                        }
                                        Action {
                                            text: "Paste"

                                            onTriggered: label1.text = "You clicked: " + text
                                        }
                                    }

                                    Menu {
                                        title: "Help"

                                        Action {
                                            text: "About"

                                            onTriggered: label1.text = "You clicked: " + text
                                        }
                                    }

                                    Layout.alignment: Qt.AlignVCenter
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "MenuBar with keyboard accelerators"

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            ColumnLayout {
                                anchors.fill: parent

                                Label {
                                    id: label2

                                    Layout.preferredHeight: menuBar2.height

                                    Layout.alignment: Qt.AlignVCenter
                                    Layout.fillWidth: true
                                }

                                MenuBar {
                                    id: menuBar2

                                    Layout.fillWidth: true

                                    Menu {
                                        title: "File"

                                        Action {
                                            text: "New"

                                            onTriggered: label2.text = "You clicked: " + text

                                            shortcut: "Ctrl+N"
                                        }
                                        Action {
                                            text: "Open"

                                            onTriggered: label2.text = "You clicked: " + text

                                            shortcut: "Ctrl+O"
                                        }
                                        Action {
                                            text: "Save"

                                            onTriggered: label2.text = "You clicked: " + text

                                            shortcut: "Ctrl+S"
                                        }
                                        Action {
                                            text: "Exit"

                                            onTriggered: label2.text = "You clicked: " + text

                                            shortcut: "Ctrl+E"
                                        }
                                    }

                                    Menu {
                                        title: "Edit"

                                        Action {
                                            text: "Undo"

                                            onTriggered: label2.text = "You clicked: " + text

                                            shortcut: "Ctrl+Z"
                                        }
                                        Action {
                                            text: "Cut"

                                            onTriggered: label2.text = "You clicked: " + text

                                            shortcut: "Ctrl+X"
                                        }
                                        Action {
                                            text: "Copy"

                                            onTriggered: label2.text = "You clicked: " + text

                                            shortcut: "Ctrl+C"
                                        }
                                        Action {
                                            text: "Paste"

                                            onTriggered: label2.text = "You clicked: " + text

                                            shortcut: "Ctrl+V"
                                        }
                                    }

                                    Menu {
                                        title: "Help"

                                        Action {
                                            text: "About"

                                            onTriggered: label2.text = "You clicked: " + text

                                            shortcut: "Ctrl+I"
                                        }
                                    }

                                    Layout.alignment: Qt.AlignVCenter
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
