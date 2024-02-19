#include "RenderEngine.hpp"
#include "RenderShader.hpp"
#include "FileSystem/FileSystem.hpp"

#include <LLGL/Window.h>
#include <LLGL/Log.h>
#include <LLGL/TypeInfo.h>
#include <LLGL/Utils/VertexFormat.h>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

static void LogCallback(const LLGL::Log::ReportType type, const char* msg, void* data)
{
	static_cast<Logger*>(data)->Log(msg);
}

void RenderEngine::Init()
{
	init_renderer();
	init_swapchain();
	init_surface();
	init_pipeline();
}

void RenderEngine::Update()
{
	const auto& window = static_cast<LLGL::Window*>(m_window);

	const RenderCommand command =
	{
		static_cast<LLGL::SwapChain*>(m_swapchain),
		static_cast<LLGL::PipelineState*>(m_graphics),
		static_cast<LLGL::Buffer*>(m_vertexBuffer),
		static_cast<LLGL::Buffer*>(m_indexBuffer),
		static_cast<LLGL::CommandBuffer*>(m_commandBuffer)
	};

	while (LLGL::Surface::ProcessEvents() && !window->HasQuit())
	{
		update_frame(command);
	}
}

void RenderEngine::init_renderer()
{
#ifdef DEBUG
	m_logger = Logger("DEBUG");
#else
	m_logger = Logger("RELEASE");
#endif

	RegisterCallback(LogCallback, &m_logger);

	LLGL::RenderSystemDescriptor renderSystemDescriptor;
	{
		renderSystemDescriptor.moduleName = "OpenGL";
		renderSystemDescriptor.debugger = &m_debugger;
	}

	m_renderer = LLGL::RenderSystem::Load(renderSystemDescriptor);
}

void RenderEngine::init_surface()
{
	// custom surface defined by GLFW

	LLGL::Window& window = LLGL::CastTo<LLGL::Window>(static_cast<LLGL::SwapChain*>(m_swapchain)->GetSurface());
	m_window = &window;

	window.SetTitle("Test Window");
	window.Show();
}

void RenderEngine::init_swapchain()
{
	// swapchain defined by swapchain descriptor

	LLGL::SwapChainDescriptor swapchainDescriptor;
	{
		swapchainDescriptor.resolution = { 800, 600 };
	}

	m_swapchain = m_renderer->CreateSwapChain(swapchainDescriptor);
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

	LLGL::VertexFormat vertexFormat;
	vertexFormat.AppendAttribute({ "aPos", LLGL::Format::RG32Float, 0 });
	vertexFormat.AppendAttribute({ "aColor", LLGL::Format::RGB32Float, 1 });

	LLGL::BufferDescriptor vertexBufferDescriptor;
	{
		vertexBufferDescriptor.size = vertices.size() * sizeof(Vertex);
		vertexBufferDescriptor.bindFlags = LLGL::BindFlags::VertexBuffer;
		vertexBufferDescriptor.vertexAttribs = vertexFormat.attributes;
	}

	m_vertexBuffer = m_renderer->CreateBuffer(vertexBufferDescriptor, vertices.data());
	m_indexBuffer = nullptr;

	std::string vs_src = ReadFile("assets/shaders/source/vert.glsl");
	std::string fs_src = ReadFile("assets/shaders/source/frag.glsl");

	LLGL::ShaderDescriptor vsDescriptor;
	{
		vsDescriptor.type = LLGL::ShaderType::Vertex;
		vsDescriptor.source = vs_src.c_str();
		vsDescriptor.sourceType = LLGL::ShaderSourceType::CodeFile;
		vsDescriptor.vertex.inputAttribs = vertexFormat.attributes;
	}

	LLGL::Shader* vsShader = m_renderer->CreateShader(vsDescriptor);
	LLGL::Shader* fsShader = m_renderer->CreateShader({ LLGL::ShaderType::Fragment, fs_src.c_str() });

	for (const auto& shader : {vsShader, fsShader})
	{
		if (const auto& report = shader->GetReport())
		{
			if (report->HasErrors())
				m_logger.Error(report->GetText());
			else
				m_logger.Warn(report->GetText());
		}
	}

	const auto& swapchain = static_cast<LLGL::SwapChain*>(m_swapchain);

	LLGL::GraphicsPipelineDescriptor psDescriptor;
	{
		psDescriptor.vertexShader = vsShader;
		psDescriptor.fragmentShader = fsShader;
		psDescriptor.renderPass = swapchain->GetRenderPass();
	}

	m_graphics = m_renderer->CreatePipelineState(psDescriptor);
	m_commandBuffer = m_renderer->CreateCommandBuffer();
}

void RenderEngine::update_frame(const RenderCommand& command)
{
	LLGL::AttachmentClear clear;
	clear.clearValue.color[0] = 1.0f;
	clear.clearValue.color[3] = 1.0f;

	command.cmdBuffer->Begin();
		command.cmdBuffer->BeginRenderPass(*command.swapchain);
			command.cmdBuffer->SetViewport(command.swapchain->GetResolution());

			command.cmdBuffer->Clear(LLGL::ClearFlags::Color);
			command.cmdBuffer->ClearAttachments(1, &clear);
			command.cmdBuffer->SetPipelineState(*command.graphicsPipeline);
			command.cmdBuffer->SetVertexBuffer(*command.vertexBuffer);
			command.cmdBuffer->Draw(3, 0);
		command.cmdBuffer->EndRenderPass();
	command.cmdBuffer->End();

	command.swapchain->Present();
}
