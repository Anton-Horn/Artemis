project "Artemis"
kind "ConsoleApp"
cppdialect "C++17"
location "%{wks.location}/Artemis"
staticruntime "on"
toolset "msc"

targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

files {"%{wks.location}/%{prj.name}/src/**.h", "%{wks.location}/%{prj.name}/src/**.cpp" }
bindirs ""

includedirs {
    "%{wks.location}/%{prj.name}/src",
    lib_includes[1],
    lib_includes[2],
    lib_includes[3]
}

--removefiles {}

filter "configurations:Debug"
    defines { "ART_DEBUG"}
    symbols "On"

filter "configurations:Release"
    defines { "ART_RELEASE" }
    optimize "On"
    symbols "off"

filter "configurations:Dist" 
    defines { "ART_DIST" }

filter "system:windows" 

    defines {
        "ART_WINDOWS"
    }

    --files {}
