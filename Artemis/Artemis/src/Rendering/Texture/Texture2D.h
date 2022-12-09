#pragma once

#include <stdint.h>
#include <string>

#include "Core/Core.h"

enum class TextureFilter {
	Nearest,
	Linear
};

enum class WrapBehavior {
	Repeat,
	ClampToEdge,
	MirrorRepeat
}; 

enum class TextureDataFormat {
	RGBA8,
	RED
};

struct Texture2DSpecification {

	WrapBehavior wrap_behavior = WrapBehavior::Repeat;
	TextureFilter mag_filter = TextureFilter::Nearest;
	TextureFilter min_filter = TextureFilter::Nearest;
	TextureDataFormat data_format = TextureDataFormat::RGBA8;

	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t bits_per_pixel = 0;

	std::string file_name;
	bool load_file = false;

	uint8_t* data = nullptr;

	bool store_image_data = false;
	bool allow_texture_pointer = false;

};

class Texture2D
{

public:

	//return value must be deleted
	static uint8_t* LoadTexture(const std::string& file_name, int& width, int& height, int& bits_per_pixel, RenderingAPI api);

	static std::shared_ptr<Texture2D> Create(const Texture2DSpecification& spec, RenderingAPI api);

	Texture2D();
	virtual ~Texture2D() = default;

	virtual void BindTextureUnit(int unit) const = 0;

	int GetWidth() const;
	int GetHeight() const;

	TextureFilter GetMagFilter() const {
		return m_mag_filter;
	}
	TextureFilter GetMinFilter() const {
		return m_min_filter;
	}
	WrapBehavior GetWrapBehavior() const {
		return m_wrap_behavior;
	}

	void SetMagFilter(TextureFilter filter) {
		m_mag_filter = filter;
	}
	void SetMinFilter(TextureFilter filter) {
		m_min_filter = filter;
	}
	void SetWrapBehavior(WrapBehavior wrap_filter) {
		m_wrap_behavior = wrap_filter;
	}

	virtual uint32_t GetRendererTexture() const = 0;

	virtual void CreateTexturePointer(uint32_t texture_renderer_id) = 0;

private: 

	bool m_allow_texture_pointer;

protected:

	uint8_t* m_texture_data = nullptr;
	bool m_delete_on_construct = true;

	std::string m_file_name;

	int m_width;
	int m_height;

	TextureFilter m_mag_filter = TextureFilter::Nearest;
	TextureFilter m_min_filter = TextureFilter::Linear;

	WrapBehavior m_wrap_behavior = WrapBehavior::ClampToEdge;

};



