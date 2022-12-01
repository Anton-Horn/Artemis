#pragma once

#include "Core/Core.h"
#include <string>

class RendererImpl;
class FrameBuffer;
class Shader;

struct Renderer2dData {

	std::shared_ptr<RendererImpl> renderer_impl;
	RenderingAPI api;

	std::shared_ptr<FrameBuffer> frame_buffer;
	std::shared_ptr<Shader> quad_shader;
	std::shared_ptr<Shader> circle_shader;

};

class Renderer2d {

private:

	Renderer2dData m_data;

public:

	void Init(RenderingAPI api);

	void Test();

	std::weak_ptr<RendererImpl> GetRendererImpl();
	std::weak_ptr<FrameBuffer> GetFrameBuffer();

};