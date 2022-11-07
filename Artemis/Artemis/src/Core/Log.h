#pragma once

#include "spdlog/spdlog.h"
#include <memory>

//Log Defines

#ifdef ART_DEBUG 
	#define ART_LOG(...) Log::s_BaseLogger->trace(__VA_ARGS__)
	#define ART_INFO(...) Log::s_BaseLogger->info(__VA_ARGS__)
	#define ART_WARN(...) Log::s_BaseLogger->warn(__VA_ARGS__)
	#define ART_ERROR(...) Log::s_BaseLogger->error(__VA_ARGS__)
#else
	#define ART_LOG(...) 
	#define ART_WARN(...) 
	#define ART_ERROR(...)
#endif

class Log {

public:

	static std::shared_ptr<spdlog::logger> s_BaseLogger;

	static void Create();
	static void Delete();

};