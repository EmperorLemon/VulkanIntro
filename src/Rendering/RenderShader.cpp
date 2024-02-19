#include "RenderShader.hpp"
#include "Logger/Logger.hpp"

#include <shaderc/shaderc.hpp>

static Logger s_logger("SHADERS");

void CompileShader(const char* filepath, const ShaderType type, const std::string& source, std::vector<uint32_t>& out, const bool optimize)
{
	const shaderc::Compiler compiler;
	shaderc::CompileOptions options;

	if (const auto& result = compiler.PreprocessGlsl(source, static_cast<shaderc_shader_kind>(type), filepath, options); result.GetCompilationStatus() != shaderc_compilation_status_success)
		s_logger.Error(result.GetErrorMessage().c_str());

	if (optimize)
		options.SetOptimizationLevel(shaderc_optimization_level_size);

	if (const auto& result = compiler.CompileGlslToSpvAssembly(source, static_cast<shaderc_shader_kind>(type), filepath, options); result.GetCompilationStatus() != shaderc_compilation_status_success)
		s_logger.Error(result.GetErrorMessage().c_str());

	const auto& module = compiler.CompileGlslToSpv(source, static_cast<shaderc_shader_kind>(type), filepath, options);

	if (module.GetCompilationStatus() != shaderc_compilation_status_success)
		s_logger.Error(module.GetErrorMessage().c_str());

	out = { module.cbegin(), module.cend() };
}
