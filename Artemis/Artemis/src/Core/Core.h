#pragma once

#include <stdint.h>
#include <memory>

#include "Debug_Test.h"

#ifdef ART_WINDOWS

#else
#error "Artemis only supports Windows"
#endif

template<typename T>
std::shared_ptr<T> GetSharedPointer(std::weak_ptr<T> weak_ptr) {

	std::shared_ptr<T> result = weak_ptr.lock();
	if (!result) ART_ABORT("Tried to dereference a weak_ptr that is expired! {0}", typeid(T).name());
	return result;
}

//Rendering, probably not the best place to define it :=)
enum class RenderingAPI {
	None,
	OpenGL,
	Direct11,
	Vulkan
};
