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
	void init();
	void update();
	void cleanup();
private:
	Logger m_logger;
	Window m_window;
};