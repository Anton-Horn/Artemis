#pragma once

#include "Core/Core.h"

#include "Rendering\Shader.h"
#include "Rendering\Vertex.h"
#include "Rendering\Texture\Texture2D.h"

#include "VertexBuffer.h"
#include "FrameBuffer.h"
#include "Texture/Texture2D.h"


struct PostRenderingData {
	Ref<Shader> PostProcessingShader;
	PostRenderingVertex Vertices[4];
	Ref<VertexBuffer> Vertexbuffer;
	Ref<Texture2D> Texture;
	int width = 1280; 
	int height = 720;
};

class PostRenderer
{

	static PostRenderingData s_RenderingData;

public:

	static void Init();

	static void DrawFrameBufferColorAttachment(FrameBuffer* framebuffer);

	static void Resize(int width, int height);

	static PostRenderingData& GetData() {
		return s_RenderingData;
	}

};



