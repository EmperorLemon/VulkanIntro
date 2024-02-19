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
	void* handle = nullptr; // native window handle
};

void GetWindowSize(const Window& window, int& width, int& height);
bool PollEvents(const Window& window);
void DestroyWindow(const Window& window);