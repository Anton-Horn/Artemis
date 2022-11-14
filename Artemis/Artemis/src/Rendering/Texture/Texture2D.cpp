
#include "Texture2D.h"

#include "Rendering/OpenGL/OpenGLTexture.h"
#include "Rendering/RenderingPipeline.h"


uint8_t* Texture2D::LoadTexture(const std::string& file_name, int& width, int& height, int& bitsperpixel)
{	
	if (RenderingPipeline::GetData().API == RenderingAPI::OpenGL) {
		return OpenGLTexture::LoadTexture(file_name, width, height, bitsperpixel);
	}

	return nullptr;
}


Ref<Texture2D> Texture2D::Create(const Texture2DSpecification& spec)
{

	if (RenderingPipeline::GetData().API == RenderingAPI::OpenGL) {
		return CreateRef<OpenGLTexture>(spec);
	}

	return nullptr;
}

Texture2D::Texture2D() {
	m_Filename = "";
	m_Width = 0;
	m_Height = 0;
}

int Texture2D::GetWidth() const
{
	return m_Width;
}

int Texture2D::GetHeight() const
{
	return m_Height;
}
void Texture2D::CreateTexturePointer(uint32_t TextureRendererID)
{

}

