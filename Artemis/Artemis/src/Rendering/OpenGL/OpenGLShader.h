#pragma once

#include "Rendering/Shader.h"
#include <string>

class OpenGLShader : public Shader
{

private:

	uint32_t m_shader_id;

public:

	OpenGLShader(const ShaderSpecification& spec);
	~OpenGLShader();

	virtual void Bind() const override;
	virtual void UnBind() const override;

};


