#include "VulkanBackend.hpp"

VkShaderModule CreateShaderModule(const VkDevice& device, const std::string& bytecode)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

	createInfo.codeSize = bytecode.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(bytecode.data());

	VkShaderModule shaderModule;

	if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
		throw std::runtime_error("Failed to create shader module!");

	return shaderModule;
}

VkPipelineShaderStageCreateInfo CreateShaderStage(const VkShaderStageFlagBits stage, const VkShaderModule& module)
{
	VkPipelineShaderStageCreateInfo shaderStageInfo = {};
	shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;

	shaderStageInfo.stage = stage;
	shaderStageInfo.module = module;
	shaderStageInfo.pName = "main";

	return shaderStageInfo;
}

void CompileShader()
{
	//ReadFile(vsPath, vs_txt);

	//PreprocessShader(vsPath, shaderc_glsl_vertex_shader,   vs_txt);

	//const std::string vs_asm = CompileFileToAssembly(vsPath, shaderc_glsl_vertex_shader,   vs_txt);

	//CompileFile(vsPath, shaderc_glsl_vertex_shader, vs_txt, vs_asm, vs_spv);

	//WriteFile("assets/shaders/binaries/vert.spv", vs_spv);
}