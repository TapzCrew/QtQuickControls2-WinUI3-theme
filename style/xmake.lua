target("QQC2-WinUI3Style")
    add_rules("qt.qmlplugin")
    set_languages("cxxlatest", "clatest")
    set_license("GPLv3")

    add_headerfiles("src/*.hpp")
    add_headerfiles("src/*.mpp")
    add_headerfiles("src/*.inl")

    add_files("src/*.cpp")
    add_files("src/*.hpp")
    add_files("*.qrc")

    set_values("qt.qmlplugin.import_name", "WinUI3Style")
    set_values("qt.qmlplugin.qmldirfile", "qml/qmldir")

    add_syslinks("WindowsApp")

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

    if is_plat("windows") then
        set_runtimes(is_mode("debug") and "MDd" or "MD")

        add_defines("_CRT_SECURE_NO_WARNINGS")
        add_cxxflags("/bigobj", "/permissive-", "/Zc:__cplusplus", "/Zc:externConstexpr", "/Zc:inline", "/Zc:lambda", "/Zc:preprocessor", "/Zc:referenceBinding", "/Zc:strictStrings", "/Zc:throwingNew")
        add_cxflags("/w44062") -- Enable warning: switch case not handled
        add_cxflags("/wd4251") -- Disable warning: class needs to have dll-interface to be used by clients of class blah blah blah
        add_cxflags("/wd4297")
    end

    after_install(function(target)
        os.mv(path.join(target:installdir(), "bin/QQC2-WinUI3Style.dll"), path.join(target:installdir(), "bin/WinUI3Style/QQC2-WinUI3Style.dll"))
    end)
