target("QQC2-WinUI3StyleAddonsImpl")
    add_rules("qt.qmlplugin")
    set_languages("cxxlatest", "clatest")
    set_license("GPLv3")

    add_headerfiles("src/*.hpp")
    add_headerfiles("src/*.mpp")
    add_headerfiles("src/*.inl")

    add_files("src/*.cpp")
    add_files("src/*.hpp")
    add_files("*.qrc")

    set_values("qt.qmlplugin.import_name", "WinUI3Style.Addons.Impl")
    set_values("qt.qmlplugin.qmldirfile", "qml/qmldir")

    add_syslinks("dwmapi")

    add_frameworks("QtCore",
                   "QtGui",
                   "QtQuick",
                   "QtQml",
                   "QtQuickTemplates2")

    add_frameworks("QtCoreprivate",
                   "QtGuiprivate",
                   "QtQuickprivate",
                   "QtQmlprivate",
                   "QtQuickControls2Implprivate",
                   "QtQuickTemplates2private")


    after_install(function(target)
        os.mv(path.join(target:installdir(), "bin/QQC2-WinUI3StyleAddonsImpl.dll"), path.join(target:installdir(), "bin/WinUI3Style/Addons/Impl/QQC2-WinUI3StyleAddonsImpl.dll"))
    end)
