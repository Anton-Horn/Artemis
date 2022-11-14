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

struct Texture2DSpecification {

	WrapBehavior WrapBehavior = WrapBehavior::Repeat;
	TextureFilter MagFilter = TextureFilter::Nearest;
	TextureFilter MinFilter = TextureFilter::Nearest;
	uint32_t Width = 0;
	uint32_t Height = 0;
	uint32_t BitsPerPixel = 0;

	std::string Filename;
	bool LoadFile = true;

	uint8_t* Data = nullptr;

	bool StoreImageData = true;
	bool AllowTexturePointer = false;

};

class Texture2D
{

public:

	//return value must be deleted
	static uint8_t* LoadTexture(const std::string& filename, int& width, int& height, int& bitsperpixel);

	static Ref<Texture2D> Create(const Texture2DSpecification& spec);

	Texture2D();
	virtual ~Texture2D() = default;

	virtual void BindTextureUnit(int unit) const = 0;

	int GetWidth() const;
	int GetHeight() const;

	TextureFilter GetMagFilter() const {
		return m_MagFilter;
	}
	TextureFilter GetMinFilter() const {
		return m_MinFilter;
	}
	WrapBehavior GetWrapBehavior() const {
		return m_WrapBehavior;
	}

	void SetMagFilter(TextureFilter filter) {
		m_MagFilter = filter;
	}
	void SetMinFilter(TextureFilter filter) {
		m_MinFilter = filter;
	}
	void SetWrapBehavior(WrapBehavior wrapfilter) {
		m_WrapBehavior = wrapfilter;
	}

	virtual uint32_t GetRendererTexture() const = 0;

	virtual void CreateTexturePointer(uint32_t TextureRendererID) = 0;

private: 

	bool m_AllowTexturePointer;

protected:

	uint8_t* m_TextureData = nullptr;
	bool m_DeleteOnDeconstruct = true;

	std::string m_Filename;

	int m_Width;
	int m_Height;

	TextureFilter m_MagFilter = TextureFilter::Nearest;
	TextureFilter m_MinFilter = TextureFilter::Linear;

	WrapBehavior m_WrapBehavior = WrapBehavior::ClampToEdge;

};



