#include "VulkanApp.hpp"

#include "VulkanBackend.hpp"
#include "Window/GLFWwindow.hpp"

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
	CreateInstance(enableValidationLayers);

	const auto& instance = GetInstance();

	SetupDebugMessenger(instance, enableValidationLayers);
	CreateWindowSurface(instance, m_window);
	SelectPhysicalDevice(instance);
	CreateLogicalDevice(enableValidationLayers);
	CreateSwapChain(GetPhysicalDevice(), GetLogicalDevice(), m_window);
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
	DestroySwapChain(GetLogicalDevice());
	DestroyLogicalDevice();

	const auto& instance = GetInstance();

	if (enableValidationLayers)
		DestroyDebugUtilsMessengerEXT(instance, nullptr);

	DestroyWindowSurface(instance);
	DestroyInstance();
	DestroyWindow(m_window);
	TerminateWindowLibrary();
}
