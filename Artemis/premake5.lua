workspace "Artemis"
configurations {"Debug", "Release", "Dist"}
architecture "x64"
startproject "Artemis"



group "Libs"


group ""

lib_includes = {}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

include "Artemis"
