#include "VulkanBackend.hpp"

#include <vulkan/vulkan_core.h>
#include <stdexcept>

void CreateInstance(void* instance)
{
	const std::vector validationLayers = { "VK_LAYER_KHRONOS_validation" };

#ifdef NDEBUG
	constexpr bool enableValidationLayers = false;
#else
	constexpr bool enableValidationLayers = true;
#endif

	if (enableValidationLayers && !CheckValidationLayerSupport(validationLayers))
		throw std::runtime_error("Validation layers requested, but not available!");

	VkApplicationInfo appInfo{};

	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

	appInfo.pApplicationName = "Application Test";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};

	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	const auto extensions = GetRequiredExtensions(enableValidationLayers);

	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
		createInfo.enabledLayerCount = 0u;

	if (vkCreateInstance(&createInfo, nullptr, reinterpret_cast<VkInstance*>(&instance)) != VK_SUCCESS)
		throw std::runtime_error("Failed to Create Instance!");
}

void DestroyInstance(void* instance)
{
	vkDestroyInstance(static_cast<VkInstance>(instance), nullptr);
}