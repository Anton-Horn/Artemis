
#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Rendering/stb_image/stb_image.h"

#include "Core/Log.h"
#include "glad/glad.h"

#include "Core/Debug_Test.h"

OpenGLTexture::~OpenGLTexture()
{
	if (m_delete_on_construct) {
		glDeleteTextures(1, &m_gl_texture_id);
	}	
	delete[] m_texture_data;
}

uint8_t* OpenGLTexture::LoadTexture(const std::string& file_name, int& width, int& height, int& bits_per_pixel)
{
	stbi_set_flip_vertically_on_load(true);
	auto texture_buffer = stbi_load(file_name.c_str() , &width, &height, &bits_per_pixel, 4);

	if (!texture_buffer) {
		ART_ABORT("Failed to load OpenGL Texture: {0}", file_name.c_str());
	}
	return texture_buffer;
}

OpenGLTexture::OpenGLTexture(const Texture2DSpecification& spec)
{

	if (spec.load_file) {

		m_file_name = spec.file_name;
		m_texture_data = stbi_load(m_file_name.c_str(), &m_width, &m_height, &m_bits_per_pixel, 4);

		if (!m_texture_data) {
			ART_ABORT("Failed to load OpenGL Texture: {0}", m_file_name.c_str());
		}

		glActiveTexture(GL_TEXTURE1);

		glGenTextures(1, &m_gl_texture_id);
		glBindTexture(GL_TEXTURE_2D, m_gl_texture_id);

		SetTextureFilters(spec);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texture_data);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (!spec.store_image_data)
			delete[] m_texture_data;
		
		return;
	}

	if (spec.width == 0 || spec.height == 0) {
		return;
	}

	if (spec.data == nullptr) {


		m_width = spec.width;
		m_height = spec.height;
		m_bits_per_pixel = 32;
		
		glActiveTexture(GL_TEXTURE1);

		glGenTextures(1, &m_gl_texture_id);
		glBindTexture(GL_TEXTURE_2D, m_gl_texture_id);

		SetTextureFilters(spec);

		uint32_t data_size = m_width * m_height * 4;

		m_texture_data = new uint8_t[data_size];

		for (uint32_t i = 0; i < (uint32_t)(m_width * m_height); i++) {
			uint32_t* ptr = (uint32_t*) m_texture_data;
			ptr[i] = 0xffffffff;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texture_data);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (!spec.store_image_data)
			delete[] m_texture_data;
		return;
	}

	m_width = spec.width;
	m_height = spec.height;
	m_bits_per_pixel = spec.bits_per_pixel;

	glActiveTexture(GL_TEXTURE1);

	glGenTextures(1, &m_gl_texture_id);
	glBindTexture(GL_TEXTURE_2D, m_gl_texture_id);

	SetTextureFilters(spec);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spec.data);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	if (spec.store_image_data) {

		uint32_t data_size = spec.width * spec.height * (spec.bits_per_pixel / 8);

		m_texture_data = new uint8_t[data_size];
		memcpy(m_texture_data, spec.data, data_size);

	}

}

void OpenGLTexture::BindTextureUnit(int unit) const
{
	glBindTextureUnit(unit, m_gl_texture_id);
}

uint32_t OpenGLTexture::GetRendererTexture() const
{
	return m_gl_texture_id;
}

void OpenGLTexture::CreateTexturePointer(uint32_t TextureRendererID)
{
	m_gl_texture_id = TextureRendererID;
	m_delete_on_construct = false;
}

void OpenGLTexture::SetTextureFilters(const Texture2DSpecification& spec)
{
	if (spec.mag_filter == TextureFilter::Linear) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if (spec.mag_filter == TextureFilter::Nearest) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	if (spec.min_filter == TextureFilter::Linear) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (spec.min_filter == TextureFilter::Nearest) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	if (spec.wrap_behavior == WrapBehavior::ClampToEdge) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else if (spec.wrap_behavior == WrapBehavior::Repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (spec.wrap_behavior == WrapBehavior::MirrorRepeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	}
}

