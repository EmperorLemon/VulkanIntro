#include "FileSystem.hpp"
#include "Logger/Logger.hpp"

#include <fstream>

static Logger s_logger("FILESYSTEM");

std::string ReadFile(const char* filepath)
{
	std::string out;

	if (std::ifstream in(filepath, std::ios::in | std::ios::binary); in)
	{
		in.seekg(0, std::ios::end);

		if (const auto size = in.tellg(); size != -1)
		{
			out.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(out.data(), size);
		}
		else
			s_logger.Error("Could not read file: {0}", filepath);
	}
	else
		s_logger.Error("Could not open file: {0}", filepath);

	return out;
}

void ReadFile(const char* filepath, std::string& out)
{
	if (std::ifstream file(filepath, std::ios::ate | std::ios::binary); file)
	{
		file.seekg(0, std::ios::end);

		if (const auto size = file.tellg(); size != -1)
		{
			out.resize(size);
			file.seekg(0, std::ios::beg);
			file.read(out.data(), size);
		}
		else
			s_logger.Error("Could not read file: {0}", filepath);
	}
	else
		s_logger.Error("Could not open file: {0}", filepath);
}
