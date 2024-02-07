#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <shaderc/shaderc.hpp>

inline void ReadFile(const char* filename, std::string& data)
{
	if (std::ifstream file(filename, std::ios::ate | std::ios::binary); file)
	{
		file.seekg(0, std::ios::end);

		if (const auto size = file.tellg(); size != -1)
		{
			data.resize(size);
			file.seekg(0, std::ios::beg);
			file.read(data.data(), size);
		}
		else
			std::cerr << "Could not read file: " << filename << std::endl;
	}
	else
		std::cerr << "Could not open file: " << filename << std::endl;
}

inline void WriteFile(const char* filename, const std::vector<uint32_t>& data)
{
	if (std::ofstream file(filename, std::ios::binary); file)
	{
		file.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size() * sizeof(uint32_t)));
		file.close();
	}
	else
	{
		std::cerr << "Could not open file for writing: " << filename << std::endl;
	}
}

// Returns GLSL shader source text after preprocessing.
inline std::string PreprocessShader(const char* filename, const shaderc_shader_kind kind, const std::string& src_text) noexcept
{
	const shaderc::Compiler compiler;
	const shaderc::CompileOptions options;

	const shaderc::PreprocessedSourceCompilationResult result = compiler.PreprocessGlsl(src_text, kind, filename, options);

	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
	{
		std::cerr << result.GetErrorMessage();
		return "";
	}

	return { result.cbegin(), result.cend() };
}

// Compiles a shader to SPIR-V assembly. Returns the assembly text as a string.
inline std::string CompileFileToAssembly(const char* filename, const shaderc_shader_kind kind, const std::string& src_text, const bool optimise = false) noexcept
{
	const shaderc::Compiler compiler;
	shaderc::CompileOptions options;

	if (optimise) options.SetOptimizationLevel(shaderc_optimization_level_size);

	const shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(src_text, kind, filename, options);

	if (result.GetCompilationStatus() != shaderc_compilation_status_success) 
	{
		std::cerr << result.GetErrorMessage();
		return "";
	}

	return { result.cbegin(), result.cend() };
}

// Compiles a shader to a SPIR-V binary. Returns the binary as a vector of 32-bit words.
inline void CompileFile(const char* filename, const shaderc_shader_kind kind, const std::string& src_text, const std::string& assembly, std::vector<uint32_t>& output, const bool optimise = false) noexcept
{
	const shaderc::Compiler compiler;
	shaderc::CompileOptions options;

	if (optimise) options.SetOptimizationLevel(shaderc_optimization_level_size);

	options.SetWarningsAsErrors();
	options.SetGenerateDebugInfo();

	const shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(src_text, kind, filename, options);
	//const shaderc::SpvCompilationResult result = compiler.AssembleToSpv(assembly.c_str(), assembly.size());

	if (result.GetCompilationStatus() != shaderc_compilation_status_success) 
	{
		std::cerr << result.GetErrorMessage();
		output = {};
	}

	output = { result.cbegin(), result.cend() };
}