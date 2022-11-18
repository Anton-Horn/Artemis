#pragma once

#include "spdlog/spdlog.h"
#include <memory>

//Log Defines

#ifdef ART_DEBUG 
	#define ART_LOG(...) Log::s_base_logger->trace(__VA_ARGS__)
	#define ART_INFO(...) Log::s_base_logger->info(__VA_ARGS__)
	#define ART_WARN(...) Log::s_base_logger->warn(__VA_ARGS__)
	#define ART_ERROR(...) Log::s_base_logger->error(__VA_ARGS__)
#else
	#define ART_LOG(...) 
	#define ART_WARN(...) 
	#define ART_ERROR(...)
#endif

class Log {

public:

	static std::shared_ptr<spdlog::logger> s_base_logger;

	static void Create();
	static void Delete();

};