#pragma once

#include "Rendering/RendererImpl.h"

#include "Rendering/IndexBuffer.h"

class OpenGLRenderer : public RendererImpl
{

private:

	size_t m_max_quads = 0;

	uint32_t* m_quad_indices = nullptr;

public:

	~OpenGLRenderer();
	OpenGLRenderer() = default;

	virtual void BeginInit() override;
	virtual void EndInit() override;
	virtual void DrawVertexBuffer(VertexBuffer* vertex_buffer, const IndexBuffer& index_buffer) override;
	virtual int GetTextureSlots() override;

	virtual void SetMaxQuads(size_t count) override;

	virtual void SetClearColor(const Color& color) override;
	virtual void Clear() override;

	virtual void SetViewport(int x, int y, uint32_t width, uint32_t height) override;

	virtual void EnableAlphaBlending() override;

	virtual void DisableAlphaBlending() override;

	virtual void EnableZBuffer() override;

	virtual void DisableZBuffer() override;
	 
};



