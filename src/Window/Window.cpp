#include "Window.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

bool Window::resized = false;

Window::Window(const uint32_t width, const uint32_t height, const char* title) : width(width), height(height), title(title)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title, nullptr, nullptr);

	glfwSetWindowUserPointer(static_cast<GLFWwindow*>(window), this);

	glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(window), [](GLFWwindow* win, [[maybe_unused]] const int x, [[maybe_unused]] const int y)
	{
		[[maybe_unused]] const auto winptr = static_cast<Window*>(glfwGetWindowUserPointer(win));

		resized = true;
	});
}

void UpdateWindow()
{
	glfwPollEvents();
}

void DestroyWindow(const Window& window)
{
	glfwDestroyWindow(static_cast<GLFWwindow*>(window.window));
	glfwTerminate();
}

bool CanCloseWindow(const Window& window)
{
	return glfwWindowShouldClose(static_cast<GLFWwindow*>(window.window));
}