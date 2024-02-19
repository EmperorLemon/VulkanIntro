#pragma once

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

	void update_frame();

#ifdef DESTROY_ALL
	void destroy_surface();
	void destroy_swapchain();
	void destroy_pipeline();
	void destroy_buffers();
#endif
private:
	Logger m_logger;
};