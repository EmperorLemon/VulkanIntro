#pragma once

#include "Window/Window.hpp"

class GLApp
{
public:
	void Run();
private:
	void InitApp();
	void UpdateApp();
	void CleanupApp();

	Window m_window;
};