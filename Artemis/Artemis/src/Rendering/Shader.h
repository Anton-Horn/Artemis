#pragma once

#include "Core/Core.h"
#include <string>

#include <filesystem>

class Shader
{
	
public:

	Shader() = default;
	virtual ~Shader() = default;

	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	virtual void SetUniform1f(float f, const char* uname) const = 0;
	virtual void SetUniform2f(float f1, float f2, const char* uname) const = 0;
	virtual void SetUniform3f(float f1, float f2, float f3, const char* uname) const = 0;
	virtual void SetUniform4f(float f1, float f2, float f3, float f4, const char* uname) const = 0;

	virtual void SetUniform1i(int i, const char* uname) const = 0;
	virtual void SetUniform2i(int i1, int i2, const char* uname) const = 0;
	virtual void SetUniform3i(int i1, int i2, int i3, const char* uname) const = 0;
	virtual void SetUniform4i(int i1, int i2, int i3, int i4, const char* uname) const = 0;

	virtual void SetUniform1ui(unsigned int i, const char* uname) const = 0;
	virtual void SetUniform2ui(unsigned int i1, unsigned int i2, const char* uname) const = 0;
	virtual void SetUniform3ui(unsigned int i1, unsigned int i2, unsigned int i3, const char* uname) const = 0;
	virtual void SetUniform4ui(unsigned int i1, unsigned int i2, unsigned int i3, unsigned int i4, const char* uname) const = 0;

	virtual void SetUniform1fa(int count, const float* data, const char* uname) const = 0;
	virtual void SetUniform2fa(int count, const float* data, const char* uname) const = 0;
	virtual void SetUniform3fa(int count, const float* data, const char* uname) const = 0;
	virtual void SetUniform4fa(int count, const float* data, const char* uname) const = 0;
							 
	virtual void SetUniform1ia(int count, const int* data, const char* uname) const = 0;
	virtual void SetUniform2ia(int count, const int* data, const char* uname) const = 0;
	virtual void SetUniform3ia(int count, const int* data, const char* uname) const = 0;
	virtual void SetUniform4ia(int count, const int* data, const char* uname) const = 0;

	virtual void SetUniformMatrix2x2(int count, const float* data, const char* uname) const = 0;
	virtual void SetUniformMatrix3x3(int count, const float* data, const char* uname) const = 0;
	virtual void SetUniformMatrix4x4(int count, const float* data, const char* uname) const = 0;

	virtual void SetUniformMatrix3x2(int count, const float* data, const char* uname) const = 0;
	virtual void SetUniformMatrix4x2(int count, const float* data, const char* uname) const = 0;

	virtual void SetUniformMatrix2x3(int count, const float* data, const char* uname) const = 0;
	virtual void SetUniformMatrix4x3(int count, const float* data, const char* uname) const = 0;

	virtual void SetUniformMatrix2x4(int count, const float* data, const char* uname) const = 0;
	virtual void SetUniformMatrix3x4(int count, const float* data, const char* uname) const = 0;

	static std::string LoadShaderSource(const std::filesystem::path& path);
	static Shader* Create(const std::string& VertexSource, const std::string& FragmentSource, RenderingAPI api);

};



