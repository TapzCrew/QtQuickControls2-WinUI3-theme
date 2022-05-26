target("WinUI3Style-example")
    set_kind("binary")
    add_rules("qt.quickapp")
    set_languages("cxxlatest", "clatest")
    set_license("GPLv3")

    add_files("src/**.cpp")
    add_files("**.qrc")

    add_frameworks("QtCore",
                   "QtGui",
                   "QtQml",
                   "QtQuickControls2")

    if is_plat("windows") then
        set_runtimes(is_mode("debug") and "MDd" or "MD")

        add_defines("_CRT_SECURE_NO_WARNINGS")
        add_cxxflags("/bigobj", "/permissive-", "/Zc:__cplusplus", "/Zc:externConstexpr", "/Zc:inline", "/Zc:lambda", "/Zc:preprocessor", "/Zc:referenceBinding", "/Zc:strictStrings", "/Zc:throwingNew")
        add_cxflags("/w44062") -- Enable warning: switch case not handled
        add_cxflags("/wd4251") -- Disable warning: class needs to have dll-interface to be used by clients of class blah blah blah
        add_cxflags("/wd4297")
    end
