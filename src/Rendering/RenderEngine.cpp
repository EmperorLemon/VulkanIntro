#include "RenderEngine.hpp"
#include "RenderShader.hpp"
#include "FileSystem/FileSystem.hpp"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

void RenderEngine::Init()
{
	init();
}

void RenderEngine::Update()
{
	while (PollEvents(m_window))
	{
		update();
	}

	cleanup();
}

void RenderEngine::init()
{
#ifdef DEBUG
	m_logger = Logger("DEBUG");
#else
	m_logger = Logger("RELEASE");
#endif

	m_window = Window(800, 600);

	bgfx::renderFrame();

	bgfx::Init init;
	{
		int width = 0, height = 0;

		GetWindowSize(m_window, width, height);

		init.platformData.nwh  = m_window.handle;
		init.resolution.width  = static_cast<uint32_t>(width);
		init.resolution.height = static_cast<uint32_t>(height);
		init.resolution.reset  = BGFX_RESET_VSYNC;
	}

	if (!bgfx::init(init))
		throw std::runtime_error("Unable to initialize bgfx context!");
}

//void RenderEngine::init_pipeline()
//{
//	struct Vertex
//	{
//		float position[2];
//		float color[3];
//	};
//
//	const std::vector<Vertex> vertices =
//	{
//		{{0.0f,  0.5f}, {1.0f, 0.0f, 0.0f}},
//		{{0.5f, -1.0f}, {0.0f, 1.0f, 0.0f}},
//		{{0.5f, -1.0f}, {0.0f, 0.0f, 1.0f}}
//	};
//}

void RenderEngine::update()
{
	bgfx::touch(0);

	bgfx::frame();
}

void RenderEngine::cleanup()
{
	bgfx::shutdown();
	DestroyWindow(m_window);
}
