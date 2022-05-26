target("WinUI3-qqc2-style")
    set_kind("shared")
    add_rules("qt.shared")
    set_languages("cxxlatest", "clatest")
    set_license("GPLv3")

    add_files("src/**.cpp")
    add_headerfiles("src/**.mpp")
    add_headerfiles("src/**.hpp")
    add_files("src/**.hpp")
    add_files("**.qrc")

    add_frameworks("QtCore",
                   "QtCoreprivate",
                   "QtGui",
                   "QtQml",
                   "QtQmlprivate",
                   "QtQuickControls2",
                   "QtQuickControls2private",
                   "QtQuickControls2Impl",
                   "QtQuickControls2Implprivate",
                   "QtQuickTemplates2",
                   "QtQuickTemplates2private")

    if is_plat("windows") then
        set_runtimes(is_mode("debug") and "MDd" or "MD")

        add_defines("_CRT_SECURE_NO_WARNINGS")
        add_cxxflags("/bigobj", "/permissive-", "/Zc:__cplusplus", "/Zc:externConstexpr", "/Zc:inline", "/Zc:lambda", "/Zc:preprocessor", "/Zc:referenceBinding", "/Zc:strictStrings", "/Zc:throwingNew")
        add_cxflags("/w44062") -- Enable warning: switch case not handled
        add_cxflags("/wd4251") -- Disable warning: class needs to have dll-interface to be used by clients of class blah blah blah
        add_cxflags("/wd4297")
    end

    after_build(function(target)
        os.cp("qml/qmldir")
    end)

includes("example/**.lua")
