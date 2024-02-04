#include "VulkanBackend.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>
//
//#include <vulkan/vulkan_win32.h>

VkSurfaceKHR surface;

void CreateWindowSurface(const VkInstance& instance, const Window& window)
{
	//VkWin32SurfaceCreateInfoKHR createInfo = {};

	//createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;

	//createInfo.hwnd = glfwGetWin32Window(static_cast<GLFWwindow*>(window.window));
	//createInfo.hinstance = GetModuleHandle(nullptr);

	//if (vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface) != VK_SUCCESS)
	//	throw std::runtime_error("Failed to create window surface!");

	if (glfwCreateWindowSurface(instance, static_cast<GLFWwindow*>(window.window), nullptr, &surface) != VK_SUCCESS)
		throw std::runtime_error("Failed to create window surface!");
}

void DestroyWindowSurface(const VkInstance& instance)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}

const VkSurfaceKHR& GetWindowSurface()
{
	return surface;
}

const char** GetRequiredWindowExtensions(uint32_t* count)
{
	return glfwGetRequiredInstanceExtensions(count);
}