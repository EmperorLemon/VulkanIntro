#pragma once

#include "Window/Window.hpp"

#include <vector>
#include <iostream> // TODO: Remove this
#include <optional>
#include <array>

#include <vulkan/vulkan.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


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

struct Vertex
{
	glm::vec2 position;
	glm::vec3 color;

	static VkVertexInputBindingDescription GetBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription = {};

		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

		attributeDescriptions.at(0).binding = 0;
		attributeDescriptions.at(0).location = 0;
		attributeDescriptions.at(0).format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions.at(0).offset = offsetof(Vertex, position);

		attributeDescriptions.at(1).binding = 0;
		attributeDescriptions.at(1).location = 1;
		attributeDescriptions.at(1).format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions.at(1).offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
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
const VkQueue& GetGraphicsQueue();
const VkQueue& GetPresentationQueue();

void CreateWindowSurface(const VkInstance& instance, const Window& window);
void DestroyWindowSurface(const VkInstance& instance);
const VkSurfaceKHR& GetWindowSurface();
const char** GetRequiredWindowExtensions(uint32_t* count);

void CreateSwapchain(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const Window& window);
void CleanupSwapchain(const VkDevice& device);
void RecreateSwapchain(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const Window& window);

SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& device);
VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, const Window& window);

void CreateImageViews(const VkDevice& device);

void CreateGraphicsPipeline(const VkDevice& device);
void DestroyGraphicsPipeline(const VkDevice& device);

void CreateRenderPass(const VkDevice& device);
void DestroyRenderPass(const VkDevice& device);

void CreateFramebuffers(const VkDevice& device);

void CreateCommandPool(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice);
void DestroyCommandPool(const VkDevice& device);

void CreateCommandBuffers(const VkDevice& device);
void RecordCommandBuffer(const VkCommandBuffer& cmdBuffer, const VkBuffer& vertexBuffer, uint32_t imageIndex);

void CreateVertexBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const std::vector<Vertex>& vertices);
void DestroyVertexBuffer(const VkDevice& device);
const VkBuffer& GetVertexBuffer();
uint32_t FindMemoryType(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

VkShaderModule CreateShaderModule(const VkDevice& device, const std::string& bytecode);
VkPipelineShaderStageCreateInfo CreateShaderStage(VkShaderStageFlagBits stage, const VkShaderModule& module);

void CreateSyncObjects(const VkDevice& device);
void DestroySyncObjects(const VkDevice& device);

void DrawFrame(const VkPhysicalDevice& physicalDevice, const VkDevice& logicalDevice, const Window& window, const VkQueue& graphicsQueue, const VkQueue& presentQueue, const VkBuffer& vertexBuffer);

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