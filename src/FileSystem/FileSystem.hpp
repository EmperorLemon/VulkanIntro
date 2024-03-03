#pragma once

#include <string>
#include <vector>

void ReadFile(const char* filepath, std::string& data);
void WriteFile(const char* filepath, const std::vector<uint32_t>& data);
void WriteFile(const char* filepath, const std::string& data);
bool CheckFile(const char* filepath);
bool FileExists(const char* filepath);