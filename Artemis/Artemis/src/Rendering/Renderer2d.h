#pragma once

#include "Core/Core.h"
#include <string>

#include <glm/glm.hpp>

class RendererImpl;
class FrameBuffer;
class Shader;

struct Renderer2dData {

	std::shared_ptr<RendererImpl> renderer_impl;
	RenderingAPI api;

	std::shared_ptr<FrameBuffer> frame_buffer;
	std::shared_ptr<Shader> quad_shader;
	std::shared_ptr<Shader> circle_shader;

	glm::mat4 projection;

};

class Renderer2d {

private:

	Renderer2dData m_data;

public:

	void Init(RenderingAPI api);

	void Test();

	void RenderText();

	void RenderQuad(const glm::mat4& transform, std::weak_ptr<Shader> shader);

	std::weak_ptr<RendererImpl> GetRendererImpl();
	std::weak_ptr<FrameBuffer> GetFrameBuffer();

};