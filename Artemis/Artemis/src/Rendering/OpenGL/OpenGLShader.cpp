
#include "OpenGLShader.h"

#include "Core/Log.h"
#include "glad/glad.h"

#include "Core/Debug_Test.h"

unsigned int OpenGLShader::GetUniformLocation(const char* uname) const
{
	return glGetUniformLocation(m_shader_id, uname);
}

OpenGLShader::OpenGLShader(const std::string& vertex_source, const std::string& fragment_source)
{
	m_shader_id = glCreateProgram();

	GLuint VertexID = glCreateShader(GL_VERTEX_SHADER);
	const char* vs = vertex_source.c_str();
	glShaderSource(VertexID, 1, &vs, 0);
	glCompileShader(VertexID);

	int result;

	glGetShaderiv(VertexID, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE) {

		int length = 0;

		glGetShaderiv(VertexID, GL_INFO_LOG_LENGTH, &length);

		char* message = new char[length];

		glGetShaderInfoLog(VertexID, length, &length, message);

		ART_LOG(vertex_source.c_str());

		ART_ABORT("[OpenGL VertexShader compilation error] {0}", message);

		delete[] message;

	}

	GLuint FragID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* fs = fragment_source.c_str();
	glShaderSource(FragID, 1, &fs, 0);
	glCompileShader(FragID);

	glGetShaderiv(FragID, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE) {

		int length = 0;

		glGetShaderiv(FragID, GL_INFO_LOG_LENGTH, &length);

		char* message = new char[length];

		glGetShaderInfoLog(FragID, length, &length, message);

		ART_ABORT("[OpenGL FragmentShader compilation error] {0}", message);

		delete[] message;

	}

	glAttachShader(m_shader_id, VertexID);
	glAttachShader(m_shader_id, FragID);

	glLinkProgram(m_shader_id);

	glDetachShader(m_shader_id, VertexID);
	glDetachShader(m_shader_id, FragID);

	glDeleteShader(VertexID);
	glDeleteShader(FragID);

}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_shader_id);
}

void OpenGLShader::SetUniform1f(float f, const char* uname) const
{
	GLuint id = GetUniformLocation(uname);
	glUniform1f(id, f);
}

void OpenGLShader::SetUniform2f(float f1, float f2, const char* uname) const
{
}

void OpenGLShader::SetUniform3f(float f1, float f2, float f3, const char* uname) const
{
}

void OpenGLShader::SetUniform4f(float f1, float f2, float f3, float f4, const char* uname) const
{
}

void OpenGLShader::SetUniform1i(int i, const char* uname) const
{
	GLuint id = GetUniformLocation(uname);
	glUniform1i(id, i);
}

void OpenGLShader::SetUniform2i(int i1, int i2, const char* uname) const
{
}

void OpenGLShader::SetUniform3i(int i1, int i2, int i3, const char* uname) const
{
}

void OpenGLShader::SetUniform4i(int i1, int i2, int i3, int i4, const char* uname) const
{
}

void OpenGLShader::SetUniform1ui(unsigned int i, const char* uname) const
{
}

void OpenGLShader::SetUniform2ui(unsigned int i1, unsigned int i2, const char* uname) const
{
}

void OpenGLShader::SetUniform3ui(unsigned int i1, unsigned int i2, unsigned int i3, const char* uname) const
{
}

void OpenGLShader::SetUniform4ui(unsigned int i1, unsigned int i2, unsigned int i3, unsigned int i4, const char* uname) const
{
}

void OpenGLShader::SetUniform1fa(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniform2fa(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniform3fa(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniform4fa(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniform1ia(int count, const int* data, const char* uname) const
{
	GLuint id = GetUniformLocation(uname);
	glUniform1iv(id, count, data);
}

void OpenGLShader::SetUniform2ia(int count, const int* data, const char* uname) const
{
}

void OpenGLShader::SetUniform3ia(int count, const int* data, const char* uname) const
{
}

void OpenGLShader::SetUniform4ia(int count, const int* data, const char* uname) const
{
}

void OpenGLShader::SetUniformMatrix2x2(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniformMatrix3x3(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniformMatrix4x4(int count, const float* data, const char* uname) const
{
	unsigned int id = GetUniformLocation(uname);
	glUniformMatrix4fv(id, 1, false, data);
}

void OpenGLShader::SetUniformMatrix3x2(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniformMatrix4x2(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniformMatrix2x3(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniformMatrix4x3(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniformMatrix2x4(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::SetUniformMatrix3x4(int count, const float* data, const char* uname) const
{
}

void OpenGLShader::Bind() const
{
	glUseProgram(m_shader_id);
}

void OpenGLShader::UnBind() const
{
	glUseProgram(0);
}



