#pragma once

#include <cstdint>
#include <string>

struct Window
{
	uint32_t width = 0u;
	uint32_t height = 0u;
	std::string title;
	void* window = nullptr;
};