#pragma once

#include "Window/Window.hpp"

class VulkanApp
{
public:
	void Run();
	void Test() noexcept;
private:
	void InitApp();
	void UpdateApp();
	void CleanupApp();

	Window m_window;
};