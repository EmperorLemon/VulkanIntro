#pragma once

#include "Logger/Logger.hpp"
#include "Window/Window.hpp"

class VulkanApp
{
public:
	void Run();
private:
	void InitApp();
	void UpdateApp();
	void CleanupApp();

	Window m_window;
	Logger m_logger;
};