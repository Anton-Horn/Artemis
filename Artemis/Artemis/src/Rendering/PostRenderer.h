#pragma once

#include "Core/Core.h"

#include "Rendering/Shader.h"
#include "Rendering/Vertex.h"
#include "Rendering/Texture\Texture2D.h"

#include "VertexBuffer.h"
#include "FrameBuffer.h"
#include "Texture/Texture2D.h"

#include "IndexBuffer.h"

struct PostRenderingData {
	std::shared_ptr<Shader> post_processing_shader;
	PostRenderingVertex vertices[4];
	std::shared_ptr<VertexBuffer> vertex_buffer;
	std::shared_ptr<Texture2D> texture;
	std::shared_ptr<FrameBuffer> frame_buffer;
	IndexBuffer index_buffer;
};

class PostRenderer
{

	PostRenderingData s_rendering_data;
	RenderingAPI m_api;

public:

	void Init(RenderingAPI api);

	void DrawFrameBufferColorAttachment(std::weak_ptr<FrameBuffer> w_frame_buffer);

	void Resize(uint32_t width, uint32_t height);

	PostRenderingData& GetData() {
		return s_rendering_data;
	}

};



