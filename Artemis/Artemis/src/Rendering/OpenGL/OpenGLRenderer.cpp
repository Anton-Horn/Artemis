
#include "OpenGLRenderer.h"


#include "Core/Log.h"
#include "Rendering/Color.h"
#include "Rendering/VertexBuffer.h"

#include "OpenGLFrameBuffer.h"
#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include <iostream>	

#include "Core/Log.h"
#include "Core/Debug_Test.h"

#ifdef ART_DEBUG

void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {

	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	ART_WARN("[OpenGL Error] {0}", message);

}

#endif


OpenGLRenderer::~OpenGLRenderer()
{
	delete[] m_quad_indices;
}

void OpenGLRenderer::BeginInit()
{
	
	

	ART_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	#ifdef ART_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebugCallback, 0);

		const GLubyte* RendererImpl = glGetString(GL_RENDERER);
		const GLubyte* Vendor = glGetString(GL_VENDOR);

		const GLubyte* Version = glGetString(GL_VERSION);
		const GLubyte* ShadingLanguageVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

		ART_LOG("[OpenGL Renderer] {0}", RendererImpl);
		ART_LOG("[OpenGL Vendor] {0}", Vendor);
		ART_LOG("[OpenGL Version] {0}", Version);
		ART_LOG("[OpenGL Shading Language Version] {0}", ShadingLanguageVersion);

#endif 

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);


	//Quad index Buffer
	m_quad_indices = nullptr;
	m_quad_indices = new unsigned int[m_max_quads * 6];

	unsigned int offset = 0;

	for (int i = 0; i < (m_max_quads * 6); i += 6) {

		m_quad_indices[i] = 0 + offset;
		m_quad_indices[i + 1] = 1 + offset;
		m_quad_indices[i + 2] = 2 + offset;
		m_quad_indices[i + 3] = 2 + offset;
		m_quad_indices[i + 4] = 3 + offset;
		m_quad_indices[i + 5] = 0 + offset;

		offset += 4;
	}

}

void OpenGLRenderer::EndInit()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLRenderer::SetClearColor(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRenderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::SetViewport(int x, int y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void OpenGLRenderer::EnableAlphaBlending()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderer::DisableAlphaBlending()
{
	glDisable(GL_BLEND);
}

void OpenGLRenderer::EnableZBuffer()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void OpenGLRenderer::DisableZBuffer()
{
	glDisable(GL_DEPTH_TEST);
}

void OpenGLRenderer::DrawVertexBuffer(VertexBuffer* vb)
{

	if (vb->GetSpec().dynamic) {
		vb->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, vb->PlaceOccupied() * vb->GetSpec().vertex_size, vb->GetVertices());
		glDrawElements(GL_TRIANGLES, (int)((vb->PlaceOccupied() / 4)) * 6, GL_UNSIGNED_INT, m_quad_indices);

		vb->UnBind();
	}
	else {
		vb->Bind();
		glDrawElements(GL_TRIANGLES, (int)((vb->PlaceOccupied() / 4)) * 6, GL_UNSIGNED_INT, m_quad_indices);
		vb->UnBind();
	}
}

int OpenGLRenderer::GetTextureSlots()
{
	int MaxTextures = 0;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MaxTextures);
	return MaxTextures;
}

void OpenGLRenderer::SetMaxQuads(size_t count)
{
	m_max_quads = count;
}




