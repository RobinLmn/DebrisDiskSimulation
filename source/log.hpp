#pragma once

#ifdef DEBUG
#pragma warning(disable:4996)
#include <spdlog/spdlog.h>
#pragma warning(default:4996)

#include <spdlog/fmt/ostr.h>
#endif

namespace sim
{
#ifdef DEBUG
	static std::shared_ptr<spdlog::logger> logger;
#endif

	void initialize_logger();
}

#ifdef DEBUG
#define LOG_ERROR(...) sim::logger->error(__VA_ARGS__)
#define LOG_WARN(...)  sim::logger->warn(__VA_ARGS__)
#define LOG_INFO(...)  sim::logger->info(__VA_ARGS__)
#define LOG_TRACE(...) sim::logger->trace(__VA_ARGS__)
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