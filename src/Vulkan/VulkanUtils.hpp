//#pragma once
//
//#include <string>
//#include <iostream>
//#include <shaderc/shaderc.hpp>
//
//// Returns GLSL shader source text after preprocessing.
//inline std::string PreprocessShader(const std::string& srcName, const shaderc_shader_kind kind, const std::string& src) noexcept
//{
//	const shaderc::Compiler compiler;
//	shaderc::CompileOptions options;
//
//	// Like -DMY_DEFINE=1
//	options.AddMacroDefinition("MY_DEFINE", "1");
//
//	const shaderc::PreprocessedSourceCompilationResult result = compiler.PreprocessGlsl(src, kind, srcName.c_str(), options);
//
//	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
//	{
//		std::cerr << result.GetErrorMessage();
//		return "";
//	}
//
//	return { result.cbegin(), result.cend() };
//}
//
//// Compiles a shader to SPIR-V assembly. Returns the assembly text as a string.
//inline std::string CompileFileToAssembly(const std::string& srcName, const shaderc_shader_kind kind, const std::string& src, const bool optimise = false) noexcept
//{
//	const shaderc::Compiler compiler;
//	shaderc::CompileOptions options;
//
//	// Like -DMY_DEFINE=1
//	options.AddMacroDefinition("MY_DEFINE", "1");
//
//	if (optimise) options.SetOptimizationLevel(shaderc_optimization_level_size);
//
//	const shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(src, kind, srcName.c_str(), options);
//
//	if (result.GetCompilationStatus() != shaderc_compilation_status_success) 
//	{
//		std::cerr << result.GetErrorMessage();
//		return "";
//	}
//
//	return { result.cbegin(), result.cend() };
//}
//
//// Compiles a shader to a SPIR-V binary. Returns the binary as a vector of 32-bit words.
//inline std::vector<uint32_t> CompileFile(const std::string& srcName, const shaderc_shader_kind kind, const std::string& source, const bool optimise = false) noexcept
//{
//	const shaderc::Compiler compiler;
//	shaderc::CompileOptions options;
//
//	// Like -DMY_DEFINE=1
//	options.AddMacroDefinition("MY_DEFINE", "1");
//
//	if (optimise) options.SetOptimizationLevel(shaderc_optimization_level_size);
//
//	const shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(source, kind, srcName.c_str(), options);
//
//	if (result.GetCompilationStatus() != shaderc_compilation_status_success) 
//	{
//		std::cerr << result.GetErrorMessage();
//		return {};
//	}
//
//	return { result.cbegin(), result.cend() };
//}