#include "RenderEngine.hpp"
#include "RenderShader.hpp"
#include "FileSystem/FileSystem.hpp"

#include <bgfx/bgfx.h>

void RenderEngine::Init()
{
	init_renderer();
	init_swapchain();
	init_surface();
	init_pipeline();
}

void RenderEngine::Update()
{
}

void RenderEngine::init_renderer()
{
#ifdef DEBUG
	m_logger = Logger("DEBUG");
#else
	m_logger = Logger("RELEASE");
#endif
}

void RenderEngine::init_surface()
{
	// custom surface defined by GLFW
}

void RenderEngine::init_swapchain()
{
	// swapchain defined by swapchain descriptor
}

void RenderEngine::init_pipeline()
{
	struct Vertex
	{
		float position[2];
		float color[3];
	};

	const std::vector<Vertex> vertices =
	{
		{{0.0f,  0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -1.0f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, -1.0f}, {0.0f, 0.0f, 1.0f}}
	};
}

void RenderEngine::update_frame()
{

}
