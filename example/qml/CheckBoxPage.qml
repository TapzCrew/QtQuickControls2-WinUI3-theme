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

            ColumnLayout {
                anchors.fill: parent

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

                Pane {
                    Layout.fillWidth: true
                    Layout.rightMargin: 12

                    RowLayout {
                        anchors.fill: parent

                        CheckBox {
                            text: "First"
                            checked: true
                        }
                        CheckBox {
                            text: "Second"
                        }
                        CheckBox {
                            text: "third"
                            checked: true
                            enabled: false
                        }
                    }
                }
            }
        }
    }
}
