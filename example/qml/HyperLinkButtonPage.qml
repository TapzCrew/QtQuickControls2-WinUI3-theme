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

    property var push
    property var menuBarToggle

    ColumnLayout {
        id: main_layout

        anchors.fill: parent

        Label {
            text: "HyperlinkButton"
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
                        text: "A HyperlinkButton appears as a text hyperlink. When a user clicks it, it opens the page you specify in the NavigateUri property in the default browser. Or you can handle its Click event, typically to navigate within your app."

                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        wrapMode: Text.WordWrap
                    }

                    Label {
                        text: "from WinUI3Style.Addons"

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
                            text: "A hyperlink button that navigates to an URI."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                HyperLinkButton {
                                    text: "Qt home page"

                                    link: "https://www.qt.io"

                                    Layout.alignment: Qt.AlignVCenter

                                    enabled: !checkbox.checked
                                }

                                Frame {
                                    Layout.fillHeight: true
                                    Layout.alignment: Qt.AlignRight

                                    CheckBox {
                                        id: checkbox

                                        text: "Disable hyperlink button"

                                        checked: false
                                    }
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        Label {
                            text: "A hyperlink button with onClicked event"

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                HyperLinkButton {
                                    text: "Go to ToggleButton"

                                    Layout.alignment: Qt.AlignVCenter

                                    enabled: !checkbox2.checked

                                    onClicked: push(4)
                                }

                                Frame {
                                    Layout.fillHeight: true
                                    Layout.alignment: Qt.AlignRight

                                    CheckBox {
                                        id: checkbox2

                                        text: "Disable hyperlink button"

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
