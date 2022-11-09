#pragma once

#include "RendererImpl.h"

enum class RenderingApi {
	OpenGL,
	Vulkan,
	DirectX
};

struct RendererSpecification {

	RenderingApi rendering_api = RenderingApi::OpenGL;

};

class Renderer {

public:


	void Create(const RendererSpecification& spec);

private:

	RendererSpecification m_Spec;

	RendererImpl* m_RendererImpl;


};