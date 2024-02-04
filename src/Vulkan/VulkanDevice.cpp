#include "VulkanBackend.hpp"

VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
VkDevice logicalDevice = VK_NULL_HANDLE;

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

		if (indices.IsComplete())
			break;

		i++;
	}

	return indices;
}