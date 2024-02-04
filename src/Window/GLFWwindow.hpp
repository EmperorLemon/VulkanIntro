#pragma once

#include "Window.hpp"

void InitWindowLibrary();
void TerminateWindowLibrary();

Window CreateWindow(uint32_t width, uint32_t height, const char* title = "Default Window");
void UpdateWindow(const Window& window);
void DestroyWindow(const Window& window);

bool CanCloseWindow(const Window& window);