#pragma once

#include <stdint.h>
#include <memory>

#ifdef ART_WINDOWS

#else

#error "Artemis only supports Windows"

#endif

//Rendering, probably not the best place to define it :=)
enum class RenderingAPI {
	None,
	OpenGL,
	Direct11,
	Vulkan
};
