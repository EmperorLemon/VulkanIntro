#include "Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

Logger::Logger(const char* name)
{
	spdlog::set_pattern("%^[%T] - %v%$");
	m_logger = spdlog::stdout_color_mt(name);
	m_logger->set_level(spdlog::level::trace);
}
