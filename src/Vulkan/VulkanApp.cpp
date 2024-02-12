#include "VulkanApp.hpp"
#include "VulkanBackend.hpp"

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

void VulkanApp::Run()
{
	m_logger = Logger("CORE");
	m_window = { 800, 600 };
	InitApp();
	UpdateApp();
	CleanupApp();
}

void VulkanApp::InitApp()
{
	CreateInstance(enableValidationLayers, m_logger);

	const auto& instance = GetInstance();

	SetupDebugMessenger(instance, enableValidationLayers, m_logger);
	CreateWindowSurface(instance, m_window);
	SelectPhysicalDevice(instance);
	CreateLogicalDevice(enableValidationLayers);

	const auto& physicalDevice = GetPhysicalDevice();
	const auto& logicalDevice = GetLogicalDevice();

	//CreateSwapchain(physicalDevice, logicalDevice, m_window);
	//CreateImageViews(logicalDevice);
	//CreateRenderPass(logicalDevice);
	//CreateGraphicsPipeline(logicalDevice);
	//CreateFramebuffers(logicalDevice);
	//CreateCommandPool(physicalDevice, logicalDevice);
	//CreateVertexBuffer(physicalDevice, logicalDevice);
	//CreateIndexBuffer(physicalDevice, logicalDevice);
	//CreateUniformBuffers(physicalDevice, logicalDevice);
	//CreateCommandBuffers(logicalDevice);
	//CreateSyncObjects(logicalDevice);
}

void VulkanApp::UpdateApp()
{
	//const auto& physicalDevice = GetPhysicalDevice();
	//const auto& logicalDevice = GetLogicalDevice();

	//const auto& graphicsQueue = GetGraphicsQueue();
	//const auto& presentQueue = GetPresentationQueue();

	//const auto& vertexBuffer = GetVertexBuffer();
	//const auto& indexBuffer = GetIndexBuffer();

	//const std::array drawBuffers = { vertexBuffer, indexBuffer };

	while (!CanCloseWindow(m_window))
	{
		UpdateWindow();
		//DrawFrame(physicalDevice, logicalDevice, m_window, graphicsQueue, presentQueue, drawBuffers);
	}

	//vkDeviceWaitIdle(logicalDevice);
}

void VulkanApp::CleanupApp()
{
	const auto& logicalDevice = GetLogicalDevice();

	//CleanupSwapchain(logicalDevice);
	//DestroyGraphicsPipeline(logicalDevice);
	//DestroyRenderPass(logicalDevice);
	//DestroyBuffers(logicalDevice);
	//DestroyDescriptorSetLayout(logicalDevice);
	//DestroySyncObjects(logicalDevice);
	//DestroyCommandPool(logicalDevice);
	DestroyLogicalDevice();

	const auto& instance = GetInstance();

	if (enableValidationLayers)
		DestroyDebugUtilsMessengerEXT(instance, nullptr);

	DestroyWindowSurface(instance);
	DestroyInstance();

	DestroyWindow(m_window);
}
