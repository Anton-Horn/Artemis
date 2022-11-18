#pragma once

#include "Core/Core.h"
#include <string>

class RendererImpl;
class FrameBuffer;
class Shader;

struct Renderer2dData {

	RendererImpl* renderer_impl;
	RenderingAPI api;

	FrameBuffer* frame_buffer;
	Shader* shader;

	const std::string vertex_source = "";
	const std::string fragment_source = "";

};

class Renderer2d {

private:

	Renderer2dData m_data;

public:

	void Init(RenderingAPI api);
	void Terminate();

	void Test();

	RendererImpl* GetRendererImpl();
	FrameBuffer* GetFrameBuffer();

};