#pragma once

class RenderEngine
{
public:
	RenderEngine() = default;
	void Init();
private:
	void init_renderer();
	void init_surface();
	void init_swapchain();
	void init_pipeline();
	void init_buffers();
};