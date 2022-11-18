#pragma once

#include "Core/Core.h"

#include "Rendering/Shader.h"
#include "Rendering/Vertex.h"
#include "Rendering/Texture\Texture2D.h"

#include "VertexBuffer.h"
#include "FrameBuffer.h"
#include "Texture/Texture2D.h"

struct PostRenderingData {
	Shader* post_processing_shader;
	PostRenderingVertex vertices[4];
	VertexBuffer* vertex_buffer;
	Texture2D* texture;
	int width = 1280; 
	int height = 720;
};

class PostRenderer
{

	PostRenderingData s_rendering_data;
	RenderingAPI m_api;

public:

	void Init(RenderingAPI api);
	void Terminate();

	void DrawFrameBufferColorAttachment(FrameBuffer* framebuffer);

	void Resize(int width, int height);

	PostRenderingData& GetData() {
		return s_rendering_data;
	}

};



