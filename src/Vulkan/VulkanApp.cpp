#include "VulkanApp.hpp"
#include "VulkanBackend.hpp"

#include "VulkanUtils.hpp"

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

void VulkanApp::Run()
{
	m_window = { 800, 600 };
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

	const auto& physicalDevice = GetPhysicalDevice();
	const auto& logicalDevice = GetLogicalDevice();

	CreateSwapchain(physicalDevice, logicalDevice, m_window);
	CreateImageViews(logicalDevice);
	CreateRenderPass(logicalDevice);
	CreateGraphicsPipeline(logicalDevice);
	CreateFramebuffers(logicalDevice);
	CreateCommandPool(physicalDevice, logicalDevice);
	CreateVertexBuffer(physicalDevice, logicalDevice, vertices);
	CreateCommandBuffers(logicalDevice);
	CreateSyncObjects(logicalDevice);
}

void VulkanApp::UpdateApp()
{
	const auto& physicalDevice = GetPhysicalDevice();
	const auto& logicalDevice = GetLogicalDevice();

	const auto& graphicsQueue = GetGraphicsQueue();
	const auto& presentQueue = GetPresentationQueue();
	const auto& vertexBuffer = GetVertexBuffer();

	while (!CanCloseWindow(m_window))
	{
		UpdateWindow();
		DrawFrame(physicalDevice, logicalDevice, m_window, graphicsQueue, presentQueue, vertexBuffer);
	}

	vkDeviceWaitIdle(logicalDevice);
}

void VulkanApp::CleanupApp()
{
	const auto& logicalDevice = GetLogicalDevice();

	CleanupSwapchain(logicalDevice);
	DestroyVertexBuffer(logicalDevice);
	DestroyGraphicsPipeline(logicalDevice);
	DestroyRenderPass(logicalDevice);
	DestroySyncObjects(logicalDevice);
	DestroyCommandPool(logicalDevice);
	DestroyLogicalDevice();

	const auto& instance = GetInstance();

	if (enableValidationLayers)
		DestroyDebugUtilsMessengerEXT(instance, nullptr);

	DestroyWindowSurface(instance);
	DestroyInstance();

	DestroyWindow(m_window);
}
