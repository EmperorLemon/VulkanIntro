#pragma once

#include "Window/Window.hpp"

#include <vector>
#include <iostream> // TODO: Remove this
#include <optional>

#include <vulkan/vulkan.h>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	[[nodiscard]] bool IsComplete() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities; // Basic surface capabilities (min/max number of images in swap chain, min/max width and height of images)
	std::vector<VkSurfaceFormatKHR> formats; // Surface formats (pixel format, color space)
	std::vector<VkPresentModeKHR> presentModes; // Available presentation modes
};

void CreateInstance(bool enableValidationLayers);
void DestroyInstance();
const VkInstance& GetInstance();

bool CheckValidationLayerSupport();
bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device);
std::vector<const char*> GetRequiredExtensions(bool enableValidationLayers);
const std::vector<const char*>& GetDeviceExtensions();
const std::vector<const char*>& GetValidationLayers();

void SelectPhysicalDevice(const VkInstance& instance);
void CreateLogicalDevice(bool enableValidationLayers);
void DestroyLogicalDevice();
const VkPhysicalDevice& GetPhysicalDevice();
const VkDevice& GetLogicalDevice();

bool IsDeviceSuitable(const VkPhysicalDevice& device);
QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device);

void CreateWindowSurface(const VkInstance& instance, const Window& window);
void DestroyWindowSurface(const VkInstance& instance);
const VkSurfaceKHR& GetWindowSurface();
const char** GetRequiredWindowExtensions(uint32_t* count);

void CreateSwapChain(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const Window& window);
void DestroySwapChain(const VkDevice& device);
void CreateImageViews(const VkDevice& device);
void DestroyImageViews(const VkDevice& device);
SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& device);
VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, const Window& window);

void CreateGraphicsPipeline(const VkDevice& device);
void DestroyGraphicsPipeline(const VkDevice& device);

void CreateRenderPass(const VkDevice& device);
void DestroyRenderPass(const VkDevice& device);

void CreateFramebuffers(const VkDevice& device);
void DestroyFramebuffers(const VkDevice& device);

void CreateCommandPool(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice);
void DestroyCommandPool(const VkDevice& device);

VkShaderModule CreateShaderModule(const VkDevice& device, const std::string& bytecode);
VkPipelineShaderStageCreateInfo CreateShaderStage(VkShaderStageFlagBits stage, const VkShaderModule& module);



/**
 * \brief A Debug Callback function
 * \param messageSeverity The first parameter specifies the severity of the message, which is one of the following flags:
 *	\n VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: Diagnostic message
 *	\n VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: Informational message like the creation of a resource
 * 	\n VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: Message about behavior that is not necessarily an error, but very likely a bug in your application
 *	\n VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: Message about behavior that is invalid and may cause crashes
 *	\n
 * \param messageType The messageType parameter can have the following values:
 *  \n VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: Some event has happened that is unrelated to the specification or performance
 *	\n VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: Something has happened that violates the specification or indicates a possible mistake
 *	\n VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: Potential non-optimal use of Vulkan
 *	\n
 * \param pCallbackData The pCallbackData parameter refers to a VkDebugUtilsMessengerCallbackDataEXT struct containing the details of the message itself, with the most important members being:
 *	\n pMessage: The debug message as a null-terminated string
 *	\n pObjects: Array of Vulkan object handles related to the message
 *	\n objectCount: Number of objects in array
 * \param userData a pointer that allows for user-generated data to be passed through the function\n
 * \return a boolean
 */
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* userData)
{
	std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

void SetupDebugMessenger(VkInstance instance, bool enableValidationLayers);
void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, const VkAllocationCallbacks* pAllocator);
const VkDebugUtilsMessengerEXT& GetDebugMessenger();