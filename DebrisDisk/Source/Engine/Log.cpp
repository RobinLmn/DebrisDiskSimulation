#include "Log.h"

#include <memory>
#include "spdlog/sinks/stdout_color_sinks.h"

namespace DebrisDisk
{
	std::shared_ptr<spdlog::logger> FLog::Logger;

	void FLog::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		Logger = spdlog::stdout_color_mt("Log:");
		Logger->set_level(spdlog::level::trace);
	}
}