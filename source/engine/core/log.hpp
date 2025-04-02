#pragma once

#ifdef DEBUG
#pragma warning(disable:4996)
#include <spdlog/spdlog.h>
#pragma warning(default:4996)

#include <spdlog/fmt/ostr.h>
#endif

namespace engine
{
	class logger
	{
	public:
		static void initialize();

	public:
#ifdef DEBUG
		static std::shared_ptr<spdlog::logger> spd_logger;
#endif
	};
}

#ifdef DEBUG
#define LOG_ERROR(...) engine::logger::spd_logger->error(__VA_ARGS__)
#define LOG_WARN(...)  engine::logger::spd_logger->warn(__VA_ARGS__)
#define LOG_INFO(...)  engine::logger::spd_logger->info(__VA_ARGS__)
#define LOG_TRACE(...) engine::logger::spd_logger->trace(__VA_ARGS__)
#else
#define LOG_ERROR(...)	
#define LOG_WARN(...)	
#define LOG_INFO(...)	
#define LOG_TRACE(...)	
#endif

#ifdef DEBUG
#define ASSERT(expression, exit_path, ...) if (!(expression)) { LOG_ERROR("Assertion failed: [{}] File [{}] Line [{}]\n{}", #expression, __FILE__, __LINE__, fmt::format(__VA_ARGS__)); __debugbreak(); exit_path; }
#define ASSERT_FATAL(expression, ...) if (!(expression)) { LOG_ERROR("Fatal assertion failed: [{}] File [{}] Line [{}]\n{}", #expression, __FILE__, __LINE__, fmt::format(__VA_ARGS__)); __debugbreak(); abort(); }
#else
#define ASSERT(expression, ...) 
#define ASSERT_FATAL(expression)
#endif