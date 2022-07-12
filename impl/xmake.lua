target("QQC2-WinUI3StyleImpl")
    add_rules("qt.qmlplugin")
    set_languages("cxxlatest", "clatest")
    set_license("GPLv3")

    add_headerfiles("src/*.hpp")

    add_files("src/*.cpp")
    add_files("src/*.hpp")
    add_files("*.qrc")

    set_values("qt.qmlplugin.import_name", "WinUI3Style.Impl")
    set_values("qt.qmlplugin.qmldirfile", "qml/qmldir")

    add_frameworks("QtCore",
                   "QtGui",
                   "QtQuick",
                   "QtQml")

    add_syslinks("dwmapi")

    after_install(function(target)
        os.mv(path.join(target:installdir(), "bin/QQC2-WinUI3StyleImpl.dll"), path.join(target:installdir(), "bin/WinUI3Style/Impl/QQC2-WinUI3StyleImpl.dll"))
    end)
