target("QQC2-WinUI3StyleAddons")
    add_rules("qt.qmlplugin")
    set_languages("cxxlatest", "clatest")
    set_license("GPLv3")

    add_headerfiles("src/*.hpp")

    add_files("src/*.cpp")
    add_files("src/*.hpp")
    add_files("*.qrc")

    set_values("qt.qmlplugin.import_name", "WinUI3Style.Addons")
    set_values("qt.qmlplugin.qmldirfile", "qml/qmldir")

    add_frameworks("QtCore",
                   "QtGui",
                   "QtQuick",
                   "QtQml",
                   "QtQuickControls2",
                   "QtQuickControls2Impl",
                   "QtQuickTemplates2")

    add_frameworks("QtCoreprivate",
                   "QtQuickprivate",
                   "QtQmlprivate",
                   "QtQuickControls2private",
                   "QtQuickControls2Implprivate",
                   "QtQuickTemplates2private")

    after_install(function(target)
        os.mv(path.join(target:installdir(), "bin/QQC2-WinUI3StyleAddons.dll"), path.join(target:installdir(), "bin/WinUI3Style/Addons/QQC2-WinUI3StyleAddons.dll"))
    end)
