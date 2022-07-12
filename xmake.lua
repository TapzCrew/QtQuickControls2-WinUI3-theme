set_xmakever("2.6.3")
set_project("QQC2-WinUI3Style")

add_rules("mode.debug", "mode.release", "mode.asan")
set_allowedmodes("debug", "release", "asan")
set_allowedplats("windows", "mingw")
set_allowedarchs("windows|x64", "mingw|x86_64")

includes("style/**.lua")
includes("impl/**.lua")
includes("addons/**.lua")
includes("addons-impl/**.lua")
includes("example/**.lua")

if is_mode("debug") then
   set_symbols("debug", "hidden")
   add_defines("QT_QML_DEBUG")
else
   set_symbols("hidden")
end

if is_plat("windows") then
    if is_mode("debug") then
        set_runtimes("MDd")
    else
        set_runtimes("MD")
    end

    add_defines("NOMINMAX", "WIN32_LEAN_AND_MEAN", { public = true })
    add_defines("_CRT_SECURE_NO_WARNINGS")
    add_cxxflags("/bigobj", "/permissive-", "/Zc:__cplusplus", "/Zc:externConstexpr", "/Zc:inline", "/Zc:lambda", "/Zc:preprocessor", "/Zc:referenceBinding", "/Zc:strictStrings", "/Zc:throwingNew")
    add_cxflags("/w44062") -- Enable warning: switch case not handled
    add_cxflags("/wd4251") -- Disable warning: class needs to have dll-interface to be used by clients of class blah blah blah
    add_cxflags("/wd4297")
end
