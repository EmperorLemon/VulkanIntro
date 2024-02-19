#pragma once

#include <string>
#include <vector>

enum ShaderType
{
	SHADER_TYPE_VERTEX,
	SHADER_TYPE_FRAGMENT,
	SHADER_TYPE_COMPUTE,
	SHADER_TYPE_GEOMETRY,
	SHADER_TYPE_TESS_CONTROL,
	SHADER_TYPE_TESS_EVALUATION
};

void CompileShader(const char* filepath, ShaderType type, const std::string& source, std::vector<uint32_t>& out, bool optimize = false);