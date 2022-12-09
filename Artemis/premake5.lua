workspace "Artemis"
configurations {"Debug", "Release", "Dist"}
architecture "x64"
startproject "Artemis"

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

group "Libs"

include "Artemis/libs/spdlog"
include "Artemis/libs/glfw"
include "Artemis/libs/glad"
include "Artemis/libs/glm"
include "Artemis/libs/freetype"

group ""

lib_includes = {
    "%{wks.location}/Artemis/libs/spdlog/include",
    "%{wks.location}/Artemis/libs/glfw/include",
    "%{wks.location}/Artemis/libs/glad/include",
    "%{wks.location}/Artemis/libs/glm/include",
    "%{wks.location}/Artemis/libs/freetype/include"
}

include "Artemis"


