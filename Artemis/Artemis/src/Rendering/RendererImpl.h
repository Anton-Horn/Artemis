#pragma once

#include "Vertex.h"
#include "Color.h"

#include "IndexBuffer.h"

class VertexBuffer;
class Shader;

class RendererImpl
{

public:

	RendererImpl() = default;

	virtual void SetMaxQuads(size_t count) = 0;

	//Is called at the beginning of the init. process
	virtual void BeginInit() = 0;
	//is called at the end of the init. process
	virtual void EndInit() = 0;

	virtual ~RendererImpl() = default;

	virtual void SetClearColor(const Color& color) = 0;
	virtual void Clear() = 0;

	virtual void EnableAlphaBlending() = 0;
	virtual void DisableAlphaBlending() = 0;

	virtual void EnableZBuffer() = 0;
	virtual void DisableZBuffer() = 0; 

	virtual void SetViewport(int x, int y, uint32_t width, uint32_t height) = 0;

	virtual void DrawVertexBuffer(std::weak_ptr<VertexBuffer> vb, const IndexBuffer& buffer ) = 0;

	virtual int GetTextureSlots() = 0;

	static std::shared_ptr<RendererImpl> Create(RenderingAPI api);

};


