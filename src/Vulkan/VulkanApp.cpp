#include "VulkanApp.hpp"

#include "VulkanBackend.hpp"

VkInstance instance = VK_NULL_HANDLE;
VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

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
	CreateInstance(instance, enableValidationLayers);
	SetupDebugMessenger(instance, debugMessenger, enableValidationLayers);
	SelectPhysicalDevice(instance);
	//CreateLogicalDevice(instance)
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
	if (enableValidationLayers)
		DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);

	DestroyInstance(instance);
	DestroyWindow(m_window);
	TerminateWindowLibrary();
}
