#pragma once

#include <cstdint>
#include <string>

struct Window
{
	Window() = default;
	Window(uint32_t width, uint32_t height, const char* title = "New Window");
	
	uint32_t width = 0u;
	uint32_t height = 0u;

	std::string title;

	void* window = nullptr;

	static bool resized;
};

void UpdateWindow();
void DestroyWindow(const Window& window);
bool CanCloseWindow(const Window& window);