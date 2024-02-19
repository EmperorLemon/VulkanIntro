#pragma once

#include <LLGL/RenderSystem.h>

#include "Logger/Logger.hpp"
#include "Window/Window.hpp"

#include <memory>

template <typename T>
class RenderObject
{
public:
	explicit RenderObject(T* ptr = nullptr) : m_ptr(ptr) {}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr.get(); }

	T* get() const { return m_ptr.get(); }

	explicit operator bool() const { return static_cast<bool>(m_ptr); }
private:
	std::shared_ptr<T> m_ptr = nullptr;
};

struct RenderCommand
{
	LLGL::SwapChain* swapchain = nullptr;
	LLGL::PipelineState* graphicsPipeline = nullptr;
	LLGL::Buffer* vertexBuffer = nullptr;
	LLGL::Buffer* indexBuffer = nullptr;
	LLGL::CommandBuffer* cmdBuffer = nullptr;
};

class RenderEngine
{
public:
	RenderEngine() = default;
	void Init();
	void Update();
private:
	void init_renderer();
	void init_surface();
	void init_swapchain();
	void init_pipeline();

	void update_frame(const RenderCommand& command);

#ifdef DESTROY_ALL
	void destroy_surface();
	void destroy_swapchain();
	void destroy_pipeline();
	void destroy_buffers();
#endif
private:
	Logger m_logger;
	LLGL::RenderingDebugger m_debugger;
private:
	LLGL::RenderSystemPtr m_renderer = nullptr;
	void* m_swapchain = nullptr;
	void* m_window = nullptr;
	void* m_graphics = nullptr; // graphics pipeline state
private:
	void* m_vertexBuffer = nullptr;
	void* m_indexBuffer = nullptr;
	void* m_commandBuffer = nullptr;
};