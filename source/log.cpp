#include "log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace sim
{
	void initialize_logger()
	{
#ifdef DEBUG
		spdlog::set_pattern("%^[%T] %n: %v%$");

		logger = spdlog::stdout_color_mt("Log:");
		logger->set_level(spdlog::level::trace);
#endif
	}
}
