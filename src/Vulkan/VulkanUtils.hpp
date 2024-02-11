#pragma once

#include <string>
#include <iostream>
#include <shaderc/shaderc.hpp>

#include "FileSystem/FileSystem.hpp"

// Returns GLSL shader source text after preprocessing.
inline std::string PreprocessShader(const char* filepath, const shaderc_shader_kind kind, const std::string& src_text) noexcept
{
	const shaderc::Compiler compiler;
	const shaderc::CompileOptions options;

	const shaderc::PreprocessedSourceCompilationResult result = compiler.PreprocessGlsl(src_text, kind, filepath, options);

	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
	{
		std::cerr << result.GetErrorMessage();
		return "";
	}

	return { result.cbegin(), result.cend() };
}

// Compiles a shader to SPIR-V assembly. Returns the assembly text as a string.
inline std::string CompileFileToAssembly(const char* filepath, const shaderc_shader_kind kind, const std::string& src_text, const bool optimise = false) noexcept
{
	const shaderc::Compiler compiler;
	shaderc::CompileOptions options;

	if (optimise) options.SetOptimizationLevel(shaderc_optimization_level_size);

	const shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(src_text, kind, filepath, options);

	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
	{
		std::cerr << result.GetErrorMessage();
		return "";
	}

	return { result.cbegin(), result.cend() };
}

// Compiles a shader to a SPIR-V binary. Returns the binary as a vector of 32-bit words.
inline void CompileFile(const char* filepath, const shaderc_shader_kind kind, const std::string& src_text, std::vector<uint32_t>& output, const bool optimise = false) noexcept
{
	const shaderc::Compiler compiler;
	shaderc::CompileOptions options;

	if (optimise) options.SetOptimizationLevel(shaderc_optimization_level_size);

	options.SetWarningsAsErrors();
	options.SetGenerateDebugInfo();

	const shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(src_text, kind, filepath, options);

	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
	{
		std::cerr << result.GetErrorMessage();
		output = {};
	}

	output = { result.cbegin(), result.cend() };
}

inline std::string GetBinaryPath(const char* filepath)
{
	const std::string binaryPath = "assets/shaders/binaries/";
	const auto extension = ".spv";

	const std::string fpath(filepath);

	const size_t pos_1 = fpath.find_last_of('/');
	const size_t pos_2 = fpath.find('.', pos_1);

	const std::string name = fpath.substr(pos_1 + 1, pos_2 - pos_1 - 1);

	return binaryPath + name + extension;
}

inline void CompileShader(const char* filepath, const shaderc_shader_kind kind, std::string& output)
{
	std::string src;
	std::vector<uint32_t> data;

	ReadFile(filepath, src);

	PreprocessShader(filepath, kind, src);
	CompileFileToAssembly(filepath, kind, src);
	CompileFile(filepath, kind, src, data);

	const auto& binPath = GetBinaryPath(filepath);

	WriteFile(binPath.c_str(), data);
	ReadFile(binPath.c_str(), output);
}

inline void ReadShader(const char* filepath, const shaderc_shader_kind kind, std::string& output)
{
	if (CheckFile(filepath) || !FileExists(GetBinaryPath(filepath).c_str()))
		CompileShader(filepath, kind, output);
	else
		ReadFile(GetBinaryPath(filepath).c_str(), output);
}