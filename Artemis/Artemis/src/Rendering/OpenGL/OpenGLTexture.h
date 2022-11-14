#pragma once

#include "Rendering\Texture\Texture2D.h"
#include "Core/Core.h"	

class OpenGLTexture : public Texture2D
{

public:

	static uint8_t* LoadTexture(const std::string& filename, int& width, int& height, int& bitperpixel);

	OpenGLTexture(const Texture2DSpecification& spec);

	OpenGLTexture() = default;

	~OpenGLTexture();

	virtual void BindTextureUnit(int unit) const override;
	virtual uint32_t GetRendererTexture() const override;
	virtual void CreateTexturePointer(uint32_t TextureRendererID) override;

private:

	int m_BitsPerPixel;

	uint32_t m_GLTextureID;

	void SetTextureFilters(const Texture2DSpecification& spec);

};



