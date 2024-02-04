#include "VulkanApp.hpp"

#include "VulkanBackend.hpp"
#include "Window/GLFWwindow.hpp"

VkInstance instance = VK_NULL_HANDLE;
VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

const std::vector validationLayers = { "VK_LAYER_KHRONOS_validation" };

void VulkanApp::Run()
{
	InitWindowLibrary();
	m_window = CreateWindow(800, 600);
	InitApp();
	UpdateApp();
	CleanupApp();
}

void VulkanApp::InitApp()
{
	CreateInstance(instance, enableValidationLayers, validationLayers);
	SetupDebugMessenger(instance, debugMessenger, enableValidationLayers);
	CreateWindowSurface(instance, m_window);
	SelectPhysicalDevice(instance);
	CreateLogicalDevice(enableValidationLayers, validationLayers);
}

void VulkanApp::UpdateApp()
{
	while (!CanCloseWindow(m_window))
	{
		UpdateWindow(m_window);
	}
}

void VulkanApp::CleanupApp()
{
	DestroyLogicalDevice();

	if (enableValidationLayers)
		DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);

	DestroyWindowSurface(instance);
	DestroyInstance(instance);
	DestroyWindow(m_window);
	TerminateWindowLibrary();
}
