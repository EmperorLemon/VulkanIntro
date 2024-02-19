#include "Window.hpp"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

Window::Window(const uint32_t width, const uint32_t height, const char* title) : width(width), height(height), title(title)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title, nullptr, nullptr);
	handle = glfwGetWin32Window(static_cast<GLFWwindow*>(window));

	glfwSetWindowUserPointer(static_cast<GLFWwindow*>(window), this);

	glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(window), [](GLFWwindow* win, [[maybe_unused]] const int x, [[maybe_unused]] const int y)
		{
			[[maybe_unused]] const auto winptr = static_cast<Window*>(glfwGetWindowUserPointer(win));
		});
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