import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

import WinUI3Style 1.0
import WinUI3Style.Addons 1.0

import "." as App

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
            text: "DropDownButton"
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
                        text: "A control that drops down a flyout of choices from which on can be chosen."

                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        wrapMode: Text.WordWrap
                    }

                    Label {
                        text: "from WinUI3Style.Addons"

                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        font.pixelSize: 12
                        font.family: "Segoe UI Light"
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "Simple DropDownButton"

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                DropDownButton {
                                    text: "Email"

                                    Layout.alignment: Qt.AlignVCenter

                                    MenuItem {
                                        text: "Send"
                                    }
                                    MenuItem {
                                        text: "Reply"
                                    }
                                    MenuItem {
                                        text: "Reply All"
                                    }
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "DropDownButton with Icons"

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                DropDownButton {
                                    font.family: WinUI3Style.iconFont
                                    text: String.fromCodePoint(0xe715)

                                    Layout.alignment: Qt.AlignVCenter

                                    MenuItem {
                                        font.family: WinUI3Style.iconFont
                                        text: String.fromCodePoint(
                                                  0xe725) + "  Send"
                                    }
                                    MenuItem {
                                        font.family: WinUI3Style.iconFont
                                        text: String.fromCodePoint(
                                                  0xe8ca) + "  Reply"
                                    }
                                    MenuItem {
                                        font.family: WinUI3Style.iconFont
                                        text: String.fromCodePoint(
                                                  0xe8c2) + "  Reply All"
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
