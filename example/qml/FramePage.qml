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

    property var push
    ColumnLayout {
        id: main_layout
        anchors.fill: parent

        Label {
            text: "Frame"
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
                        text: "Frame is used to layout a logical group of controls together, within a visual frame."

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

                    Frame {
                        Layout.fillWidth: true
                        Layout.rightMargin: 12

                        ColumnLayout {
                            anchors.fill: parent

                            Button {
                                text: "First"
                            }
                            Button {
                                text: "Second"
                            }
                            Button {
                                text: "Third"
                            }
                        }
                    }
                }
            }
        }
    }
}
