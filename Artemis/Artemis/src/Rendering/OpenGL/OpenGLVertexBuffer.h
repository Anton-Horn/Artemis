#pragma once

#include "Core/Core.h"
#include "Rendering\VertexBuffer.h"


class OpenGLVertexBuffer : public VertexBuffer
{

private:

	uint32_t m_vb_id;
	uint32_t m_vao_id;

public:
	
	OpenGLVertexBuffer(const VertexBufferSpec& spec);
	OpenGLVertexBuffer(const VertexBufferSpec& spec, void* data);
	~OpenGLVertexBuffer();		

	virtual void Bind() const override;
	virtual void UnBind() const override;

};




