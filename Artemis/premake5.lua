workspace "Artemis"
configurations {"Debug", "Release", "Dist"}
architecture "x64"
startproject "Artemis"


outputdir = "%{cfg.buildcfg}-%{cfg.system}"

group "Libs"

include "Artemis/libs/spdlog"

group ""

lib_includes = {
    "%{wks.location}/Artemis/libs/spdlog/include"
}

include "Artemis"


