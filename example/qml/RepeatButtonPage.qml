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

    ColumnLayout {
        id: main_layout

        anchors.fill: parent

        Label {
            text: "RepeatButton"
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
                        text: "The RepeatButton control is like a stadard Button, except that the Click event occurs continuously while the user presses the RepeatButton."

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
                            text: "A simple RepeatButton with text content."

                            font.family: "Segoe UI Semibold"
                            font.pixelSize: 20
                        }

                        App.ControlPane {
                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Button {
                                    text: "Click and hold"

                                    Layout.alignment: Qt.AlignVCenter

                                    autoRepeat: true

                                    onClicked: internal.clickCount += 1

                                    enabled: !checkbox.checked
                                }

                                Label {
                                    id: label_btn_1

                                    text: (internal.clickCount
                                           === 0) ? "" : ("Number of clicks: "
                                                          + internal.clickCount)
                                }

                                Frame {
                                    Layout.alignment: Qt.AlignRight

                                    CheckBox {
                                        id: checkbox

                                        text: "Disable RepeatButton"
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    QtObject {
        id: internal

        property int clickCount: 0
    }
}
