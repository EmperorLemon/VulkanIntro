#pragma once

#include <cstdint>
#include <string>

struct Window
{
	uint32_t width = 0u;
	uint32_t height = 0u;
	std::string title;
	void* window = nullptr;
};

void InitWindowLibrary();
void TerminateWindowLibrary();

const char** GetRequiredWindowExtensions(uint32_t* count);

Window CreateWindow(uint32_t width, uint32_t height, const char* title = "Default Window");
void UpdateWindow(const Window& window);
void DestroyWindow(const Window& window);

bool CanCloseWindow(const Window& window);