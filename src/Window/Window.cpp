#include "Window.hpp"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <stdexcept>

Window::Window(const uint32_t width, const uint32_t height, const char* title) : width(width), height(height), title(title)
{
	if (!glfwInit())
		throw std::runtime_error("Unable to initialze glfw context!");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title, nullptr, nullptr);
	handle = glfwGetWin32Window(static_cast<GLFWwindow*>(window));
}

void GetWindowSize(const Window& window, int& width, int& height)
{
	glfwGetWindowSize(static_cast<GLFWwindow*>(window.window), &width, &height);
}

bool PollEvents(const Window& window)
{
	glfwPollEvents();

	return !glfwWindowShouldClose(static_cast<GLFWwindow*>(window.window));
}

void DestroyWindow(const Window& window)
{
	glfwDestroyWindow(static_cast<GLFWwindow*>(window.window));
	glfwTerminate();
}