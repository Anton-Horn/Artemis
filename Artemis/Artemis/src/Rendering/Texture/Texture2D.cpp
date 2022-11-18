
#include "Texture2D.h"
#include "Rendering/OpenGL/OpenGLTexture.h"


uint8_t* Texture2D::LoadTexture(const std::string& file_name, int& width, int& height, int& bitsperpixel, RenderingAPI api)
{	
	if (api == RenderingAPI::OpenGL) {
		return OpenGLTexture::LoadTexture(file_name, width, height, bitsperpixel);
	}

	return nullptr;
}


Texture2D* Texture2D::Create(const Texture2DSpecification& spec, RenderingAPI api)
{

	if (api == RenderingAPI::OpenGL) {
		return new OpenGLTexture(spec);
	}

	return nullptr;
}

Texture2D::Texture2D() {
	m_file_name = "";
	m_width = 0;
	m_height = 0;
}

int Texture2D::GetWidth() const
{
	return m_width;
}

int Texture2D::GetHeight() const
{
	return m_height;
}
void Texture2D::CreateTexturePointer(uint32_t TextureRendererID)
{

}

