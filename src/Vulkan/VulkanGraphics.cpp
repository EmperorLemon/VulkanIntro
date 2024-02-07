#include "VulkanBackend.hpp"

#include "VulkanUtils.hpp"

void CreateGraphicsPipeline(const VkDevice& device)
{
	std::string vs_src, fs_src;

	ReadFile("assets/shaders/binaries/vert.spv", vs_src);
	ReadFile("assets/shaders/binaries/frag.spv", fs_src);

	const VkShaderModule& vs_module = CreateShaderModule(device, vs_src);
	const VkShaderModule& fs_module = CreateShaderModule(device, fs_src);

	VkPipelineShaderStageCreateInfo shaderStages[] = { CreateShaderStage(VK_SHADER_STAGE_VERTEX_BIT, vs_module), CreateShaderStage(VK_SHADER_STAGE_FRAGMENT_BIT, fs_module) };

	vkDestroyShaderModule(device, fs_module, nullptr);
	vkDestroyShaderModule(device, vs_module, nullptr);
}