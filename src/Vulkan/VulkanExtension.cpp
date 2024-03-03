#include "VulkanBackend.hpp"

#include <set>

const std::vector validationLayers = { "VK_LAYER_KHRONOS_validation" };
const std::vector deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

bool CheckValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
			return false;
	}

	return true;
}

bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions)
		requiredExtensions.erase(extension.extensionName);

	return requiredExtensions.empty();
}

std::vector<const char*> GetRequiredExtensions(const bool enableValidationLayers)
{
	uint32_t extensionCount = 0u;
	const char** windowExtensions = GetRequiredWindowExtensions(&extensionCount);

	std::vector extensions(windowExtensions, windowExtensions + extensionCount);

	if (enableValidationLayers)
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return extensions;
}

const std::vector<const char*>& GetDeviceExtensions()
{
	return deviceExtensions;
}

const std::vector<const char*>& GetValidationLayers()
{
	return validationLayers;
}