#pragma once

#include <spdlog/spdlog.h>
#include <memory>

class Logger
{
public:
	Logger() = default;
	explicit Logger(const char* name);

	template <typename... Args>
	void Info(const char* fmt, Args&&... args)
	{
		if (m_logger)
		{
			const auto& msg = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			m_logger->info(msg);
		}
		else
			throw std::runtime_error("Failed to log info!");
	}

	template <typename... Args>
	void Log(const char* fmt, Args&&... args)
	{
		if (m_logger)
		{
			const auto& msg = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			m_logger->trace(msg);
		}
		else
			throw std::runtime_error("Failed to log info!");
	}

	template <typename... Args>
	void Warn(const char* fmt, Args&&... args)
	{
		if (m_logger)
		{
			const auto& msg = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			m_logger->warn(msg);
		}
		else
			throw std::runtime_error("Failed to log info!");
	}

	template <typename... Args>
	void Error(const char* fmt, Args&&... args)
	{
		if (m_logger)
		{
			const auto& msg = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			m_logger->error(msg);
		}
		else
			throw std::runtime_error("Failed to log info!");
	}

	template <typename... Args>
	void Critical(const char* fmt, Args&&... args)
	{
		if (m_logger)
		{
			const auto& msg = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			m_logger->critical(msg);
		}
		else
			throw std::runtime_error("Failed to log info!");
	}
private:
	std::shared_ptr<spdlog::logger> m_logger = nullptr;
};
