project "glad"
kind "StaticLib"
location "%{wks.location}/Artemis/libs/%{prj.name}"
staticruntime "on"
language "C"

targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

files {"%{wks.location}/Artemis/libs/%{prj.name}/include/**.h", "%{wks.location}/Artemis/libs/%{prj.name}/src/**.c" }

includedirs {
    "%{wks.location}/Artemis/libs/%{prj.name}/include/",
}

filter "configurations:Debug"
    symbols "On"

filter "configurations:Release"
    optimize "On"
    symbols "off"

filter "configurations:Dist" 
    optimize "On"
    symbols "off"
