#pragma once

#include "Renderer/RendererImpl.h"

class OpenGLRenderer : public RendererImpl {
	// Geerbt �ber RendererImpl
	virtual void Create() override;
};