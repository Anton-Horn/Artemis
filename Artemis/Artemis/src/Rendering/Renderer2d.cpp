#include "Renderer2d.h"

#include "Core/Debug_Test.h"

#include "OpenGL/OpenGLFrameBuffer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLShader.h"

#include "IndexBuffer.h"

#include "Core/Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "OpenGL/OpenGLVertexBuffer.h"

#include <cstdlib>

#include <freetype/freetype.h>

#include <ft2build.h>

#include <map>

#include <glad/glad.h>

void Renderer2d::Init(RenderingAPI api)
{

	m_data.api = api;

	if (m_data.api == RenderingAPI::OpenGL) {
		m_data.renderer_impl = RendererImpl::Create(m_data.api);

		m_data.renderer_impl->BeginInit();
		m_data.renderer_impl->EndInit();

		std::string vertex_source = Shader::LoadShaderSource("Assets/Shaders/QuadShader.vert");
		std::string fragment_source = Shader::LoadShaderSource("Assets/Shaders/QuadShader.frag");
		m_data.quad_shader = Shader::Create(vertex_source, fragment_source, m_data.api);

		vertex_source = Shader::LoadShaderSource("Assets/Shaders/CircleShader.vert");
		fragment_source = Shader::LoadShaderSource("Assets/Shaders/CircleShader.frag");
		m_data.circle_shader = Shader::Create(vertex_source, fragment_source, m_data.api);

		FrameBufferSpecification spec = {};
		spec.width = Application::GetWindow().GetSpec().width;
		spec.height = Application::GetWindow().GetSpec().height;
		spec.samples = 4;
		spec.attachments = {FramebufferTextureFormat::RGBA8};

		m_data.frame_buffer = FrameBuffer::Create(spec, m_data.api);
		
	}
	else {
		ART_ABORT("Tried to initiliaze the renderer with an unknown rendering api!");
	}

	m_data.projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f);

}


void Renderer2d::Test()
{
	
	m_data.renderer_impl->EnableAlphaBlending();

	m_data.frame_buffer->Bind();
	m_data.frame_buffer->ClearColorAttachment(0, Color(0.1f, 0.1f, 0.1f, 1.0f));

	VertexBufferSpec spec;
	spec.attributes.attributes = { {VertexBufferDataType::FLOAT, 3}, {VertexBufferDataType::FLOAT, 4}, {VertexBufferDataType::FLOAT, 2} };
	spec.buffer_size = 4;
	spec.dynamic = false;
	spec.vertex_size = sizeof(Vertex);

	glm::vec2 p1 = {Application::GetInput().GetMouseX() - 400.0f, 300.0f - Application::GetInput().GetMouseY()};
	glm::vec2 p2 = {0.5f * 400.0f, -0.5f * 300.0f};

	float x_lenght = p2.x - p1.x;
	float y_lenght = p2.y - p1.y;

	float lenght = glm::sqrt(x_lenght * x_lenght + y_lenght * y_lenght);
	float width = 1.0f;

	glm::mat4 square_transform = glm::translate(glm::mat4(1.0f), {p1.x, p1.y, 0.0f}) * glm::rotate(glm::mat4(1.0f), std::atan2(y_lenght, x_lenght) , glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::scale(glm::mat4(1.0f), { lenght, width, 1.0f });

	 square_transform = glm::scale(glm::mat4(1.0f), { 200.0f * 1.1f, 400.0f * 1.1f, 1.0f });

	glm::mat4 circle_transform = glm::translate(glm::mat4(1.0f), {p1.x, p1.y, 0.0f}) * glm::scale(glm::mat4(1.0f), { 10.0f, 10.0f, 1.0f });

	//glm::vec4 origin_offset = {0.5f, -0.5f, 0.0f, 0.0f};
	glm::vec4 origin_offset = { 0.0f, 0.0f, 0.0f, 0.0f };

	Vertex circle_data[4] = { {-0.5f,  0.5f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 1.0f},
					   {-0.5f, -0.5f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0.0f},
					   { 0.5f, -0.5f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.0f},
					   { 0.5f,  0.5f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f} };

	Vertex quad_data[4] = { {-0.5f + origin_offset.x,  0.5f + origin_offset.y, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 1.0f},
					   {-0.5f + origin_offset.x, -0.5f + origin_offset.y, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0.0f},
					   { 0.5f + origin_offset.x, -0.5f + origin_offset.y, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.0f},
					   { 0.5f + origin_offset.x,  0.5f + origin_offset.y, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f} };
	ART_LOG("----");
	for (Vertex& vertex : quad_data) {
		glm::vec3* ptr = (glm::vec3*) &vertex;
		glm::vec4 rotated_value = glm::vec4(*ptr, 1.0f);
		rotated_value = square_transform * rotated_value;
		*ptr = rotated_value;
		
		ART_LOG("{0} / {1}", rotated_value.x, rotated_value.y);
	}
	ART_LOG("----");

	for (Vertex& vertex : circle_data) {
		glm::vec3* ptr = (glm::vec3*)&vertex;
		glm::vec4 rotated_value = glm::vec4(*ptr, 1.0f);
		rotated_value = circle_transform * rotated_value;
		*ptr = rotated_value;
	}


	std::shared_ptr<VertexBuffer> circle_vertex_buffer = VertexBuffer::Create(spec, circle_data, RenderingAPI::OpenGL);
	std::shared_ptr<VertexBuffer> quad_vertex_buffer = VertexBuffer::Create(spec, quad_data, RenderingAPI::OpenGL);

	IndexBuffer index_buffer;

	uint8_t indicies[] = { 0, 1 ,2, 2, 3, 0};
	index_buffer.SetData(IndexBufferType::UNSIGNED_CHAR, indicies, sizeof(indicies));

	m_data.quad_shader->Bind();
	m_data.quad_shader->SetUniform1f(90.0f, "u_radius");
	m_data.quad_shader->SetUniform2f(200.0f, 400.0f, "u_size");
	m_data.quad_shader->SetUniformMatrix4x4(1, (const float*)&projection_matrix, "u_projection_matrix");
	m_data.renderer_impl->DrawVertexBuffer(quad_vertex_buffer, index_buffer);
	m_data.quad_shader->UnBind();

	m_data.circle_shader->Bind();
	m_data.circle_shader->SetUniformMatrix4x4(1, (const float*)&projection_matrix, "u_projection_matrix");
	m_data.renderer_impl->DrawVertexBuffer(circle_vertex_buffer, index_buffer);
	m_data.circle_shader->UnBind();

	m_data.frame_buffer->UnBind();
}

struct Character {
	std::shared_ptr<Texture2D> texture;  // ID handle of the glyph texture
	glm::ivec2 size;       // Size of glyph
	glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
	uint32_t advance;    // Offset to advance to next glyph
};

std::map<char, Character> Characters;

void Renderer2d::RenderText()
{

	FT_Library ft;
	
	ART_ASSERT_S(FT_Init_FreeType(&ft));

	FT_Face face;
	ART_ASSERT_S(FT_New_Face(ft, "Assets/Fonts/Poppins/Poppins-Regular.ttf", 0, &face));
	ART_ASSERT_S(FT_Set_Pixel_Sizes(face, 0, 48));

	ART_ASSERT_S(FT_Load_Char(face, 'X', FT_LOAD_RENDER));

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph 
		ART_ASSERT_S(FT_Load_Char(face, c, FT_LOAD_RENDER));

		Texture2DSpecification spec;
		spec.width = face->glyph->bitmap.width;
		spec.height = face->glyph->bitmap.rows;
		spec.data_format = TextureDataFormat::RED;
		spec.data = face->glyph->bitmap.buffer;
		spec.mag_filter = TextureFilter::Linear;
		spec.min_filter = TextureFilter::Linear;
		spec.wrap_behavior = WrapBehavior::ClampToEdge;
		std::shared_ptr<Texture2D> texture = Texture2D::Create(spec, RenderingAPI::OpenGL);

		// now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

}

void Renderer2d::RenderQuad(const glm::mat4& transform, std::weak_ptr<Shader> shader)
{

	VertexBufferSpec spec;
	spec.attributes.attributes = { {VertexBufferDataType::FLOAT, 3}, {VertexBufferDataType::FLOAT, 4}, {VertexBufferDataType::FLOAT, 2} };
	spec.buffer_size = 4;
	spec.dynamic = false;
	spec.vertex_size = sizeof(Vertex);

	glm::vec4 position_1 = glm::vec4(-0.5f, 0.5f, 0.0f, 0.0f) * transform;
	glm::vec4 position_2 = glm::vec4(-0.5f, -0.5f, 0.0f, 0.0f) * transform;
	glm::vec4 position_3 = glm::vec4(0.5f, -0.5f, 0.0f, 0.0f) * transform;
	glm::vec4 position_4 = glm::vec4(0.5f, 0.5f, 0.0f, 0.0f) * transform;

	Vertex quad_data[] = {{ position_1.x, position_1.y, position_1.z, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 1.0f },
						  { position_2.x, position_2.y, position_2.z, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0.0f },
						  { position_3.x, position_3.y, position_3.z, Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.0f },
						  { position_4.x, position_4.y, position_4.z, Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f }};	

	std::shared_ptr<VertexBuffer> quad_vertex_buffer = VertexBuffer::Create(spec, quad_data, RenderingAPI::OpenGL);

	IndexBuffer index_buffer;

	uint8_t indicies[] = { 0, 1 ,2, 2, 3, 0 };
	index_buffer.SetData(IndexBufferType::UNSIGNED_CHAR, indicies, sizeof(indicies));

	m_data.quad_shader->Bind();
	m_data.quad_shader->SetUniform1f(90.0f, "u_radius");
	m_data.quad_shader->SetUniform2f(200.0f, 400.0f, "u_size");
	m_data.quad_shader->SetUniformMatrix4x4(1, (const float*)&m_data.projection, "u_projection_matrix");
	m_data.renderer_impl->DrawVertexBuffer(quad_vertex_buffer, index_buffer);
	m_data.quad_shader->UnBind();

}

std::weak_ptr<RendererImpl> Renderer2d::GetRendererImpl()
{
	return m_data.renderer_impl;
}

std::weak_ptr<FrameBuffer> Renderer2d::GetFrameBuffer()
{
	return m_data.frame_buffer;
}
