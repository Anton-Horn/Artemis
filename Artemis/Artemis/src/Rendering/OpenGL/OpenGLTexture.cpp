
#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Rendering/stb_image/stb_image.h"

#include "Core/Log.h"
#include "glad/glad.h"

#include "Core/Debug_Test.h"

OpenGLTexture::~OpenGLTexture()
{
	if (m_DeleteOnDeconstruct) {
		glDeleteTextures(1, &m_GLTextureID);
	}	
	delete[] m_TextureData;
}

uint8_t* OpenGLTexture::LoadTexture(const std::string& file_name, int& width, int& height, int& bitperpixel)
{
	stbi_set_flip_vertically_on_load(true);
	auto TextureBuffer = stbi_load(file_name.c_str() , &width, &height, &bitperpixel, 4);

	if (!TextureBuffer) {
		ART_ABORT("Failed to load OpenGL Texture: {0}", file_name.c_str());
	}
	return TextureBuffer;
}

OpenGLTexture::OpenGLTexture(const Texture2DSpecification& spec)
{

	if (spec.LoadFile) {

		m_Filename = spec.Filename;
		m_TextureData = stbi_load(m_Filename.c_str(), &m_Width, &m_Height, &m_BitsPerPixel, 4);

		if (!m_TextureData) {
			ART_ABORT("Failed to load OpenGL Texture: {0}", m_Filename.c_str());
		}

		glActiveTexture(GL_TEXTURE1);

		glGenTextures(1, &m_GLTextureID);
		glBindTexture(GL_TEXTURE_2D, m_GLTextureID);

		SetTextureFilters(spec);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureData);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (!spec.StoreImageData)
			delete[] m_TextureData;
		
		return;
	}

	if (spec.Width == 0 || spec.Height == 0) {
		return;
	}

	if (spec.Data == nullptr) {


		m_Width = spec.Width;
		m_Height = spec.Height;
		m_BitsPerPixel = 32;
		
		glActiveTexture(GL_TEXTURE1);

		glGenTextures(1, &m_GLTextureID);
		glBindTexture(GL_TEXTURE_2D, m_GLTextureID);

		SetTextureFilters(spec);

		uint32_t data_size = m_Width * m_Height * 4;

		m_TextureData = new uint8_t[data_size];

		for (uint32_t i = 0; i < (uint32_t)(m_Width * m_Height); i++) {
			uint32_t* ptr = (uint32_t*) m_TextureData;
			ptr[i] = 0xffffffff;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureData);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (!spec.StoreImageData)
			delete[] m_TextureData;
		return;
	}

	m_Width = spec.Width;
	m_Height = spec.Height;
	m_BitsPerPixel = spec.BitsPerPixel;

	glActiveTexture(GL_TEXTURE1);

	glGenTextures(1, &m_GLTextureID);
	glBindTexture(GL_TEXTURE_2D, m_GLTextureID);

	SetTextureFilters(spec);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spec.Data);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	if (spec.StoreImageData) {

		uint32_t data_size = spec.Width * spec.Height * (spec.BitsPerPixel / 8);

		m_TextureData = new uint8_t[data_size];
		memcpy(m_TextureData, spec.Data, data_size);

	}

}

void OpenGLTexture::BindTextureUnit(int unit) const
{
	glBindTextureUnit(unit, m_GLTextureID);
}

uint32_t OpenGLTexture::GetRendererTexture() const
{
	return m_GLTextureID;
}

void OpenGLTexture::CreateTexturePointer(uint32_t TextureRendererID)
{
}

void OpenGLTexture::CreateTexturePointer(uint32_t TextureRendererID)
{
	m_GLTextureID = TextureRendererID;
	m_DeleteOnDeconstruct = false;
}

void OpenGLTexture::SetTextureFilters(const Texture2DSpecification& spec)
{
	if (spec.MagFilter == TextureFilter::Linear) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if (spec.MagFilter == TextureFilter::Nearest) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	if (spec.MinFilter == TextureFilter::Linear) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (spec.MinFilter == TextureFilter::Nearest) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	if (spec.WrapBehavior == WrapBehavior::ClampToEdge) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else if (spec.WrapBehavior == WrapBehavior::Repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (spec.WrapBehavior == WrapBehavior::MirrorRepeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	}
}

