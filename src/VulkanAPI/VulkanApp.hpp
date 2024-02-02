#pragma once

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
};