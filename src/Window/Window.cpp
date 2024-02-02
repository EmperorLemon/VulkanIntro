#include "Window.hpp"

#include <GLFW/glfw3.h>

void InitWindowLibrary()
{
	glfwInit();
}

void TerminateWindowLibrary()
{
	glfwTerminate();
}

Window CreateWindow(const uint32_t width, const uint32_t height, const char* title)
{
	Window window{ width, height, std::string(title), nullptr };

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window.window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title, nullptr, nullptr);

	return window;
}

void UpdateWindow(const Window& window)
{
	glfwPollEvents();
}

void DestroyWindow(const Window& window)
{
	glfwDestroyWindow(static_cast<GLFWwindow*>(window.window));
}

const char** GetRequiredWindowExtensions(uint32_t* count)
{
	return glfwGetRequiredInstanceExtensions(count);
}

bool CanCloseWindow(const Window& window)
{
	return glfwWindowShouldClose(static_cast<GLFWwindow*>(window.window));
}