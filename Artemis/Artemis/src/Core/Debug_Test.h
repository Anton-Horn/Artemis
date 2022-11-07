#pragma once

#include "Log.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef ART_WINDOWS

	#define ART_ABORT(...) {ART_ERROR(__VA_ARGS__); __debugbreak(); }
	#define ART_ASSERT(x) if ( (x) ) {ART_INFO("Assert \"{0}\" passed! [{2}:{1}]", TOSTRING(x), __LINE__, __FILE__); } else {ART_ABORT("Assert \"{0}\" failed! [{2}:{1}]", TOSTRING(x), __LINE__, __FILE__);}
#endif



