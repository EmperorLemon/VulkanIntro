#include "VulkanApp.hpp"

#include "VulkanBackend.hpp"

VkInstance instance;

void VulkanApp::Run()
{
	InitWindowLibrary();
	m_window = CreateWindow(800, 600);
	InitApp();
	UpdateApp();
	CleanupApp();
}

void VulkanApp::InitApp()
{
	CreateInstance(instance);
}

void VulkanApp::UpdateApp()
{
	while (!CanCloseWindow(m_window))
	{
		UpdateWindow(m_window);
	}
}

void VulkanApp::CleanupApp()
{
	DestroyInstance(instance);
	DestroyWindow(m_window);
	TerminateWindowLibrary();
}
