set_xmakever("2.6.3")
set_project("QQC2-WinUI3Style")

add_rules("mode.debug", "mode.release", "mode.releasedbg", "mode.asan")
set_allowedmodes("debug", "release", "releasedbg", "asan")
set_allowedplats("windows", "mingw")
set_allowedarchs("windows|x64", "mingw|x86_64")

includes("style/**.lua")
includes("impl/**.lua")
includes("addons/**.lua")
includes("addons-impl/**.lua")
includes("example/**.lua")

if is_mode("release") then
   set_symbols("hidden")
else
   set_symbols("debug", "hidden")
   add_defines("QT_QML_DEBUG")
end
