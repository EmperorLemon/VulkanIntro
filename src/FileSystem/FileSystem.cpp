#include "FileSystem.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <set>

using namespace std::chrono_literals;

bool FileExists(const char* filepath)
{
	const auto s = std::filesystem::file_status{};

	return status_known(s) ? exists(s) : std::filesystem::exists(filepath);
}

void ReadFile(const char* filepath, std::string& data)
{
	if (std::ifstream file(filepath, std::ios::ate | std::ios::binary); file)
	{
		file.seekg(0, std::ios::end);

		if (const auto size = file.tellg(); size != -1)
		{
			data.resize(size);
			file.seekg(0, std::ios::beg);
			file.read(data.data(), size);
		}
		else
			std::cerr << "Could not read file: " << filepath << std::endl;
	}
	else
		std::cerr << "Could not open file: " << filepath << std::endl;
}

static void ReadFile(const char* filepath, std::set<std::string>& data)
{
	std::ifstream file(filepath);

	if (!file.is_open())
	{
		std::cerr << "Could not open file: " << filepath << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		data.emplace(line);
	}

	file.close();
}

void WriteFile(const char* filepath, const std::vector<uint32_t>& data)
{
	if (std::ofstream file(filepath, std::ios::binary); file)
	{
		file.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size() * sizeof(uint32_t)));
		file.close();
	}
	else
		std::cerr << "Could not open file for writing: " << filepath << std::endl;
}

void WriteFile(const char* filepath, const std::string& data)
{
	if (std::ofstream file(filepath, std::ios::binary); file)
	{
		file.write(data.data(), static_cast<std::streamsize>(data.size()));
		file.close();
	}
	else
		std::cerr << "Could not open file for writing: " << filepath << std::endl;
}

static void AppendToFile(const char* filepath, const std::vector<std::string>& data)
{
	if (std::ofstream file(filepath, std::ios::app | std::ios_base::out); file)
	{
		std::ranges::copy(data, std::ostream_iterator<std::string>(file, "\n"));
		file.close();
	}
	else
		std::cerr << "Could not open file for writing: " << filepath << std::endl;
}

static void AppendToFile(const char* filepath, const std::string& data)
{
	if (std::ofstream file(filepath, std::ios::app | std::ios_base::out); file)
	{
		file.write(data.data(), static_cast<std::streamsize>(data.size()));
		file.close();
	}
	else
		std::cerr << "Could not open file for writing: " << filepath << std::endl;
}

static bool CreateMetafile(const char* filepath, const std::filesystem::file_time_type& time)
{
	std::stringstream ss;
	ss << time << '\n';

	const std::string metafile = std::string(filepath) + ".meta";

	if (FileExists(metafile.c_str()))
	{
		std::set<std::string> r_data;
		std::vector<std::string> w_data;

		ReadFile(metafile.c_str(), r_data);

		const auto& value = ss.str().substr(0, ss.str().find_last_of('\n'));

		if (r_data.contains(value))
			return false;

		w_data.emplace_back(value);

		AppendToFile(metafile.c_str(), w_data);
	}
	else
		WriteFile(metafile.c_str(), ss.str());

	return true;
}

bool CheckFile(const char* filepath)
{
	const std::filesystem::file_time_type& ftime = last_write_time(std::filesystem::path(filepath));

	return CreateMetafile(filepath, ftime);
}