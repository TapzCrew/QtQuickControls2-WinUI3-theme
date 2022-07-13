target("WinUI3Style-example")
    set_kind("binary")
    add_rules("qt.quickapp")
    set_languages("cxxlatest", "clatest")

    set_license("GPLv3")

    add_files("src/*.cpp")
    add_files("*.qrc")

    add_frameworks("QtCore",
                   "QtGui",
                   "QtQml",
                   "QtQuick",
                   "QtQuickControls2")

    set_values("qt.deploy.qmldir", "qml/")
    set_values("qt.deploy.flags", "--no-translations", "--no-virtualkeyboard")
