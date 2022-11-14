#pragma once

#include "Rendering/Renderer.h"

class OpenGLRenderer : public Renderer
{

private:

	size_t m_MaxQuads = 0;

	unsigned int* m_QuadIndices = nullptr;

public:

	~OpenGLRenderer();
	OpenGLRenderer() = default;

	virtual void BeginInit() override;
	virtual void EndInit() override;
	virtual void DrawVertexBuffer(VertexBuffer* vb) override;
	virtual int GetTextureSlots() override;

	virtual void SetMaxQuads(size_t count) override;

	virtual void SetClearColor(const Color& color) override;
	virtual void Clear() override;

	virtual void SetViewport(int x, int y, int width, int height) override;

	virtual void EnableAlphaBlending() override;

	virtual void DisableAlphaBlending() override;

	virtual void EnableZBuffer() override;

	virtual void DisableZBuffer() override;
	 
};



