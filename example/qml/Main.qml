import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

import WinUI3Style 1.0
import WinUI3Style.Addons 1.0

import "." as App

MicaApplicationWindow {
    id: window

    width: 640
    height: 480

    minimumWidth: 500
    minimumHeight: 200

    visible: true
    title: qsTr("Gallery")

    WinUI3Style.theme: WinUI3Style.Theme.Dark

    titleBarExpanded: true
    property var stack_indices: []

    titleBar: Row {
        id: titlebar

        spacing: 6

        leftPadding: 4
        topPadding: 4

        Row {
            spacing: 4

            ToolButton {
                font.family: WinUI3Style.iconFont
                text: String.fromCodePoint(0xe830)

                enabled: stack_view.depth > 1

                onClicked: {
                    stack_view.pop()

                    stack_indices.pop()
                    if (stack_indices.length === 0)
                        list_view.currentIndex = -1
                    else
                        list_view.currentIndex = stack_indices[stack_indices.length - 1]
                }
            }

            ToolButton {
                font.family: WinUI3Style.iconFont
                text: String.fromCodePoint(0xe790)

                onClicked: window.WinUI3Style.theme = (window.WinUI3Style.theme === WinUI3Style.Theme.Dark) ? WinUI3Style.Theme.Light : WinUI3Style.Theme.Dark
            }

            ToolButton {
                font.family: WinUI3Style.iconFont
                text: String.fromCodePoint(0xe700)

                visible: !window.showSideMenu
                enabled: !window.showSideMenu

                onClicked: window.openSideMenu()
            }
        }

        Label {
            id: window_title

            text: window.title

            anchors.verticalCenter: parent.verticalCenter

            font.pixelSize: 12
            font.weight: 450
            font.family: "Segoe UI Semibold"
        }
    }

    menuBar: MenuBar {
        id: menubar

        visible: false

        Menu {
            title: "File"

            Action {
                text: "Close"

                onTriggered: window.close()
            }
        }

        Menu {
            title: "About"

            Action {
                text: "About"
            }
        }
    }

    sideMenu: ListView {
        id: list_view

        focus: true
        currentIndex: -1

        clip: true

        boundsBehavior: Flickable.StopAtBounds
        spacing: 4

        delegate: ItemDelegate {
            width: list_view.width - 14

            text: model.title

            highlighted: ListView.isCurrentItem

            onClicked: window.stackViewPush(index)
        }

        model: ListModel {
            id: model

            ListElement {
                title: "Button"
                source: "qrc:/qml/ButtonPage.qml"
            }
            ListElement {
                title: "DropDownButton"
                source: "qrc:/qml/DropDownButtonPage.qml"
            }
            ListElement {
                title: "HyperLinkButton"
                source: "qrc:/qml/HyperLinkButtonPage.qml"
            }
            ListElement {
                title: "RepeatButton"
                source: "qrc:/qml/RepeatButtonPage.qml"
            }
            ListElement {
                title: "ToggleButton"
                source: "qrc:/qml/ToggleButtonPage.qml"
            }
            ListElement {
                title: "SplitButton"
                source: "qrc:/qml/SplitButtonPage.qml"
            }
            ListElement {
                title: "CheckBox"
                source: "qrc:/qml/CheckBoxPage.qml"
            }
            ListElement {
                title: "Frame"
                source: "qrc:/qml/FramePage.qml"
            }
            ListElement {
                title: "Slider"
                source: "qrc:/qml/SliderPage.qml"
            }
            ListElement {
                title: "MenuBar"
                source: "qrc:/qml/MenuBarPage.qml"
            }
        }

        ScrollBar.vertical: ScrollBar {}
    }

    MainStackView {
        id: stack_view

        anchors.fill: parent

        initialItem: App.MainPage {
            push: window.push
        }
    }

    function stackViewPush(index) {
        if (list_view.currentIndex === index)
            return

        stack_indices.push(index)
        list_view.currentIndex = index

        stack_view.push(model.get(index).source, {
                            "push": stackViewPush,
                            "menuBarToggle": menuBarToggle
                        })

        if (!window.showSideMenu)
            window.closeSideMenu()
    }

    function menuBarToggle() {
        menubar.visible = !menubar.visible
    }
}
