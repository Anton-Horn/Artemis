#include "Renderer2d.h"

#include "Core/Debug_Test.h"

#include "OpenGL/OpenGLFrameBuffer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLShader.h"

#include "IndexBuffer.h"

#include "Core/Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Renderer2d::Init(RenderingAPI api)
{

	m_data.api = api;

	if (m_data.api == RenderingAPI::OpenGL) {
		m_data.renderer_impl = RendererImpl::Create(m_data.api);

		m_data.renderer_impl->BeginInit();
		m_data.renderer_impl->EndInit();

		std::string vertex_source = Shader::LoadShaderSource("Assets/Shaders/QuadShader.vert");
		std::string fragment_source = Shader::LoadShaderSource("Assets/Shaders/QuadShader.frag");
		m_data.QuadShader = Shader::Create(vertex_source, fragment_source, m_data.api);

		vertex_source = Shader::LoadShaderSource("Assets/Shaders/CircleShader.vert");
		fragment_source = Shader::LoadShaderSource("Assets/Shaders/CircleShader.frag");
		m_data.CircleShader = Shader::Create(vertex_source, fragment_source, m_data.api);

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
	delete m_data.QuadShader;
	delete m_data.CircleShader;
	delete m_data.renderer_impl;
}

void Renderer2d::Test()
{
	
	m_data.renderer_impl->EnableAlphaBlending();

	m_data.frame_buffer->Bind();
	m_data.frame_buffer->ClearColorAttachment(0, Color(0.1f, 0.1f, 0.1f, 1.0f));

	VertexBufferSpec spec;
	spec.attributes = { {VertexBufferDataType::FLOAT, 3}, {VertexBufferDataType::FLOAT, 4}, {VertexBufferDataType::FLOAT, 2} };
	spec.buffer_size = 4;
	spec.dynamic = false;
	spec.vertex_size = sizeof(Vertex);

	Vertex circle_data[4] = { {-0.5f,  0.5f, 0.0f, Color(1.0f, 0.0f, 1.0f, 1.0f), 0.0f, 1.0f},
					   {-0.5f, -0.5f, 0.0f, Color(1.0f, 0.0f, 1.0f, 1.0f), 0.0f, 0.0f},
					   { 0.5f, -0.5f, 0.0f, Color(1.0f, 0.0f, 1.0f, 1.0f), 1.0f, 0.0f},
					   { 0.5f,  0.5f, 0.0f, Color(1.0f, 0.0f, 1.0f, 1.0f), 1.0f, 1.0f}};

	Vertex quad_data[4] = { {-0.5f,  0.5f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 1.0f},
					   {-0.5f, -0.5f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0.0f},
					   { 0.5f, -0.5f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.0f},
					   { 0.5f,  0.5f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f} };

	ART_LOG("{0} / {1}", Application::GetInput().GetMouseX(), Application::GetInput().GetMouseY());
	glm::vec2 p1 = {Application::GetInput().GetMouseX() - 400.0f, Application::GetInput().GetMouseY() - 400.0f};



	glm::vec2 p2 = {0.5f * 400.0f, -0.5f * 300.0f};

	glm::mat4 projection_matrix = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f);

	float x_lenght = glm::abs(p1.x) + glm::abs(p2.x);
	float y_lenght = glm::abs(p1.y) + glm::abs(p2.y);

	float lenght = glm::sqrt(x_lenght * x_lenght + y_lenght * y_lenght);
	float width = 10.0f;

	glm::mat4 transform = glm::mat4(1.0f);

	transform = glm::rotate(glm::mat4(1.0f), glm::acos(y_lenght / lenght), glm::vec3(0.0f, 0.0f, 1.0f)) *
	glm::scale(glm::mat4(1.0f), {lenght, 10.0f, 1.0f});

	for (Vertex& vertex : quad_data) {
		glm::vec3* ptr = (glm::vec3*) &vertex;
		glm::vec4 rotated_value = glm::vec4(*ptr, 1.0f);
		rotated_value = transform * rotated_value;
		*ptr = rotated_value;
	}

	for (Vertex& vertex : circle_data) {
		glm::vec3* ptr = (glm::vec3*)&vertex;
		glm::vec4 rotated_value = glm::vec4(*ptr, 1.0f);
		rotated_value = transform * rotated_value;
		*ptr = rotated_value;
	}


	VertexBuffer* circle_vertex_buffer = VertexBuffer::Create(spec, circle_data, RenderingAPI::OpenGL);
	VertexBuffer* quad_vertex_buffer = VertexBuffer::Create(spec, quad_data, RenderingAPI::OpenGL);

	IndexBuffer index_buffer;

	uint8_t indicies[] = { 0, 1 ,2, 2, 3, 0};
	index_buffer.SetData(IndexBufferType::UNSIGNED_CHAR, indicies, sizeof(indicies));

	m_data.QuadShader->Bind();
	m_data.QuadShader->SetUniformMatrix4x4(1, (const float*)&projection_matrix, "u_projection_matrix");
	m_data.renderer_impl->DrawVertexBuffer(quad_vertex_buffer, index_buffer);
	m_data.QuadShader->UnBind();

	/*m_data.CircleShader->Bind();
	m_data.renderer_impl->DrawVertexBuffer(circle_vertex_buffer, index_buffer);
	m_data.CircleShader->UnBind();*/

	delete circle_vertex_buffer;
	delete quad_vertex_buffer;
	m_data.frame_buffer->UnBind();
}

RendererImpl* Renderer2d::GetRendererImpl()
{
	return m_data.renderer_impl;
}

FrameBuffer* Renderer2d::GetFrameBuffer()
{
	return m_data.frame_buffer;
}
