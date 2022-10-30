project "NAME"
kind "APPLICATION_KIND"
cppdialect "C++17"
location "%{wks.location}/Artemis/libs/%{prj.name}"
staticruntime "on"

targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

files {"%{wks.location}/Artemis/libs/%{prj.name}/FILE_DIR/**.h", "%{wks.location}/Artemis/libs/%{prj.name}/FILE_DIR/**.cpp" }

includedirs {
    "%{wks.location}/Artemis/libs/%{prj.name}/FILE_DIR/",
}

--removefiles {}

filter "configurations:Debug"
    symbols "On"

filter "configurations:Release"
    optimize "On"
    symbols "off"

filter "configurations:Dist" 
    optimize "On"
    symbols "off"
