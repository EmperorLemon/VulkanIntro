#include "VulkanBackend.hpp"

#include <set>

VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
VkDevice logicalDevice = VK_NULL_HANDLE;

VkQueue graphicsQueue = VK_NULL_HANDLE;
VkQueue presentQueue = VK_NULL_HANDLE;

void SelectPhysicalDevice(const VkInstance& instance)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
		throw std::runtime_error("Failed to find GPUs with Vulkan support!");

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (IsDeviceSuitable(device))
		{
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE)
		throw std::runtime_error("Failed to find a suitable GPU!");
}

void CreateLogicalDevice(const bool enableValidationLayers, const std::vector<const char*>& validationLayers)
{
	const QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	float queuePriority = 1.0f;

	for (uint32_t queueFamily : uniqueQueueFamilies) 
	{
		VkDeviceQueueCreateInfo queueCreateInfo = {};

		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		queueCreateInfos.push_back(queueCreateInfo);
	}

	const VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo createInfo = {};

	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
		createInfo.enabledLayerCount = 0;

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS)
		throw std::runtime_error("Failed to create logical device!");

	vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(logicalDevice, indices.presentFamily.value(), 0, &presentQueue);
}

void DestroyLogicalDevice()
{
	vkDestroyDevice(logicalDevice, nullptr);
}

bool IsDeviceSuitable(const VkPhysicalDevice& device)
{
	const QueueFamilyIndices indices = FindQueueFamilies(device);

	return indices.IsComplete();
}

bool IsDeviceSuitable(const VkDevice& device)
{
	return true;
}

QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device)
{
	QueueFamilyIndices indices = {};

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;

	for (const auto& queueFamily : queueFamilies)
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.graphicsFamily = i;

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, GetWindowSurface(), &presentSupport);

		if (presentSupport)
			indices.presentFamily = i;

		if (indices.IsComplete())
			break;

		i++;
	}

	return indices;
}