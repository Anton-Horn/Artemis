#pragma once

#include "Renderer/RendererImpl.h"

class OpenGLRenderer : public RendererImpl {
	// Geerbt über RendererImpl
	virtual void Create() override;
};