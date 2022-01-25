#pragma once

#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>

namespace DebrisDisk
{
	class FLog
	{
	public:
		void Init();

	public:
		static std::shared_ptr<spdlog::logger> Logger;
	};
}

#define LOG_FATAL(...)         ::DebrisDisk::FLog::Logger->fatal(__VA_ARGS__)
#define LOG_ERROR(...)         ::DebrisDisk::FLog::Logger->error(__VA_ARGS__)
#define LOG_WARN(...)          ::DebrisDisk::FLog::Logger->warn(__VA_ARGS__)
#define LOG_INFO(...)          ::DebrisDisk::FLog::Logger->info(__VA_ARGS__)
#define LOG_TRACE(...)         ::DebrisDisk::FLog::Logger->trace(__VA_ARGS__)
