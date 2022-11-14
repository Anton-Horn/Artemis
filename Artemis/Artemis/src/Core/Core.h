#pragma once

#include <stdint.h>
#include <memory>

#ifdef ART_WINDOWS

#else

#error "Artemis only supports Windows"

#endif

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename ... Args>
static Ref<T> CreateRef(Args&& ... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ptr = std::unique_ptr<T>;

template <typename T, typename ... Args>
static Ptr<T> CreatePtr(Args&& ... args) {
	return std::make_unique<T>(std::forward<Args>(args)...);
}