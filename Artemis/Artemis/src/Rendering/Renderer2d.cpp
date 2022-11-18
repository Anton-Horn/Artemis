#include "Renderer2d.h"

#include "Core/Debug_Test.h"

#include "OpenGL/OpenGLFrameBuffer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLShader.h"

#include "Core/Application.h"

void Renderer2d::Init(RenderingAPI api)
{

	m_data.api = api;

	if (m_data.api == RenderingAPI::OpenGL) {
		m_data.renderer_impl = RendererImpl::Create(m_data.api);

		m_data.renderer_impl->BeginInit();
		m_data.renderer_impl->EndInit();

		m_data.shader = Shader::Create(m_data.vertex_source, m_data.fragment_source, m_data.api);

		FrameBufferSpecification spec = {};
		spec.width = Application::GetWindow().GetSpec().width;
		spec.height = Application::GetWindow().GetSpec().height;
		
		spec.attachments = {FramebufferTextureFormat::RGBA8};

		m_data.frame_buffer = FrameBuffer::Create(spec, m_data.api);

	}
	else {
		ART_ABORT("Tried to initiliaze the renderer with an unknown rendering api!");
	}

}

void Renderer2d::Terminate()
{
	delete m_data.frame_buffer;
	delete m_data.shader;
	delete m_data.renderer_impl;
}

void Renderer2d::Test()
{
}

RendererImpl* Renderer2d::GetRendererImpl()
{
	return m_data.renderer_impl;
}

FrameBuffer* Renderer2d::GetFrameBuffer()
{
	return m_data.frame_buffer;
}
