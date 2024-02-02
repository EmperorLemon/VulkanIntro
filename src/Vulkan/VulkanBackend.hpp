#pragma once

#include <cstdint>
#include <vector>

#include <vulkan/vulkan.h>

void CreateInstance(void* instance);
void DestroyInstance(void* instance);

bool CheckValidationLayerSupport(const std::vector<const char*>& validationLayers);
std::vector<const char*> GetRequiredExtensions(bool enableValidationLayers);