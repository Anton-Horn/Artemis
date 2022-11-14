#pragma once

#include "Core/Core.h"
#include "Rendering\VertexBuffer.h"


class OpenGLVertexBuffer : public VertexBuffer
{

private:

	uint32_t m_VB_ID;
	uint32_t m_VAO_ID;

public:
	
	OpenGLVertexBuffer(const VertexBufferSpec& spec);
	OpenGLVertexBuffer(const VertexBufferSpec& spec, void* data);
	~OpenGLVertexBuffer();		

	virtual void Bind() const override;
	virtual void UnBind() const override;

};




