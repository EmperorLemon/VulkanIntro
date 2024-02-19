#include "RenderEngine.hpp"
#include "RenderShader.hpp"
#include "FileSystem/FileSystem.hpp"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

bgfx::VertexBufferHandle vbh;
bgfx::ProgramHandle program;

void RenderEngine::Init()
{
	init();
}

void RenderEngine::Update()
{
	prepare();
	
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

		GetFramebufferSize(m_window, width, height);

		init.platformData.nwh  = m_window.handle;
		init.type = bgfx::RendererType::OpenGL;
		init.resolution.width  = static_cast<uint32_t>(width);
		init.resolution.height = static_cast<uint32_t>(height);
		init.resolution.reset  = BGFX_RESET_VSYNC;
#ifdef DEBUG
		init.debug = true;
#else
		init.debug = false;
#endif
	}

	if (!bgfx::init(init))
		throw std::runtime_error("Unable to initialize bgfx context!");
}

void RenderEngine::prepare()
{
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x556677FF, 1.0f);
	bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

	struct Vertex
	{
		float position[2];
		float  color[3];
	};

	constexpr Vertex vertices[] =
	{
		{{0.0f,  0.5f}, {255, 0,   255}},
		{{0.5f, -1.0f}, {0,   255,   0}},
		{{0.5f, -1.0f}, {0,   0,   255}}
	};

	bgfx::VertexLayout layout;

	layout.begin(bgfx::RendererType::OpenGL)
		.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0,   3, bgfx::AttribType::Float)
	.end();

	vbh = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), layout);

	std::string vs_src, fs_src;
	std::vector<uint32_t> vs_bin, fs_bin;

	const char* vs_path = "assets/shaders/source/shader.vert";
	const char* fs_path = "assets/shaders/source/shader.frag";

	ReadFile(vs_path, vs_src);
	ReadFile(fs_path, fs_src);

	CompileShader(vs_path, SHADER_TYPE_VERTEX,   vs_src, vs_bin);
	CompileShader(fs_path, SHADER_TYPE_FRAGMENT, fs_src, fs_bin);

	const size_t vs_size = sizeof(uint32_t) * vs_bin.size();
	const bgfx::Memory* vs_memory = bgfx::alloc(static_cast<uint32_t>(vs_size));
	std::memcpy(vs_memory->data, vs_bin.data(), vs_size);

	const size_t fs_size = sizeof(uint32_t) * fs_bin.size();
	const bgfx::Memory* fs_memory = bgfx::alloc(static_cast<uint32_t>(fs_size));
	std::memcpy(fs_memory->data, fs_bin.data(), fs_size);

	const auto& vertex = bgfx::createShader(vs_memory);
	const auto& fragment = bgfx::createShader(fs_memory);

	program = bgfx::createProgram(vertex, fragment);

	m_frames = 0;
}

void RenderEngine::update()
{
	if (Window::resized)
	{
		int width = 0, height = 0;
		GetFramebufferSize(m_window, width, height);

		bgfx::reset(static_cast<uint32_t>(width), static_cast<uint32_t>(height), BGFX_RESET_VSYNC);
		bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

		Window::resized = false;
	}

	bgfx::setVertexBuffer(0, vbh);

	//bgfx::touch(0);
	bgfx::submit(0, program);
	bgfx::frame();

	m_frames++;
}

void RenderEngine::cleanup()
{
	bgfx::shutdown();
	DestroyWindow(m_window);
}
