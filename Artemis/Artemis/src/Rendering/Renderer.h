#pragma once

#include "Vertex.h"
#include "Color.h"


class VertexBuffer;
class FrameBuffer;

class Renderer
{

public:

	Renderer() = default;

	virtual void SetMaxQuads(size_t count) = 0;

	//Is called at the beginning of the init. process
	virtual void BeginInit() = 0;
	//is called at the end of the init. process
	virtual void EndInit() = 0;

	virtual ~Renderer() = default;

	virtual void SetClearColor(const Color& color) = 0;
	virtual void Clear() = 0;

	virtual void EnableAlphaBlending() = 0;
	virtual void DisableAlphaBlending() = 0;

	virtual void EnableZBuffer() = 0;
	virtual void DisableZBuffer() = 0;

	virtual void SetViewport(int x, int y, int width, int height) = 0;

	virtual void DrawVertexBuffer(VertexBuffer* vb) = 0;

	virtual int GetTextureSlots() = 0;

};


