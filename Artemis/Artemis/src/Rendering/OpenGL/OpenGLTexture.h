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

	int m_bits_per_pixel = 0;

	uint32_t m_gl_texture_id = 0;

	void SetTextureFilters(const Texture2DSpecification& spec);

};



