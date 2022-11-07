#include "Log.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <vector>

std::shared_ptr<spdlog::logger> Log::s_BaseLogger;

void Log::Create()
{

	std::vector<spdlog::sink_ptr> sinks;
	sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	sinks[0]->set_pattern("%^%n: [%T] %v%$");

	sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Artemis.log"));
	sinks[1]->set_pattern("%^%n: [%T] %v%$");

	s_BaseLogger = std::make_shared<spdlog::logger>("Artemis", sinks.begin(), sinks.end());
	spdlog::register_logger(s_BaseLogger);
	s_BaseLogger->set_level(spdlog::level::trace);
	s_BaseLogger->flush_on(spdlog::level::trace);
	

}

void Log::Delete()
{
	spdlog::shutdown();
}
