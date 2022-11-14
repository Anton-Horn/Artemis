
#include "OpenGLVertexBuffer.h"


#include "Core\Log.h"
#include "glad\glad.h"



OpenGLVertexBuffer::OpenGLVertexBuffer(const VertexBufferSpec& spec)
{
	m_Specification = spec;
	m_Specification.Dynamic = true;

	glGenVertexArrays(1, &m_VAO_ID);
	glBindVertexArray(m_VAO_ID);

	glGenBuffers(1, &m_VB_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB_ID);
	glBufferData(GL_ARRAY_BUFFER, spec.BufferSize * m_Specification.VertexSize, nullptr, GL_DYNAMIC_DRAW);

	int index = 0;
	size_t offset = 0;
	for (auto& attrib : m_Specification.Attributes.Attributes) {
		glEnableVertexAttribArray(index);
		switch (attrib.DataType) {
		case VertexBufferDataType::FLOAT:
			glVertexAttribPointer(index, (GLint)attrib.DataCount, GL_FLOAT, GL_FALSE, (GLsizei)m_Specification.VertexSize, (void*) offset);
			offset += (int) sizeof(float) * attrib.DataCount;
			break;
		case VertexBufferDataType::INT:
			glVertexAttribIPointer(index, (GLint)attrib.DataCount, GL_INT, (GLsizei) m_Specification.VertexSize, (void*)offset);
			offset += (int) sizeof(int) * attrib.DataCount;
			break;
		case VertexBufferDataType::BYTE:
			glVertexAttribIPointer(index, (GLint)attrib.DataCount, GL_BYTE, (GLsizei)m_Specification.VertexSize, (void*)offset);
			offset += (int) sizeof(char) * attrib.DataCount;
			break;
		case VertexBufferDataType::UNSIGNED_INT:
			glVertexAttribIPointer(index, (GLint)attrib.DataCount, GL_UNSIGNED_INT, (GLsizei)m_Specification.VertexSize, (void*)offset);
			offset += (int) sizeof(int) * attrib.DataCount;
			break;
		case VertexBufferDataType::UNSIGNED_BYTE:
			glVertexAttribIPointer(index, (GLint)attrib.DataCount, GL_UNSIGNED_BYTE, (GLsizei)m_Specification.VertexSize, (void*)offset);
			offset += (int) sizeof(char) * attrib.DataCount;
			break;
		}
		index++;
	}

	UnBind();

	AllocateBuffer();
	glBindVertexArray(0);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const VertexBufferSpec& spec, void* data)
{
	m_Specification = spec;
	m_Specification.Dynamic = false;

	glGenVertexArrays(1, &m_VAO_ID);
	glBindVertexArray(m_VAO_ID);

	glGenBuffers(1, &m_VB_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB_ID);
	glBufferData(GL_ARRAY_BUFFER, m_Specification.BufferSize * m_Specification.VertexSize, data, GL_STATIC_DRAW);

	int index = 0;
	size_t offset = 0;
	for (auto& attrib : m_Specification.Attributes.Attributes) {
		glEnableVertexAttribArray(index);
		switch (attrib.DataType) {
		case VertexBufferDataType::FLOAT:
			glVertexAttribPointer(index, (GLint) attrib.DataCount, GL_FLOAT, GL_FALSE, (GLint)m_Specification.VertexSize, (void*)offset);
			offset += sizeof(float) * attrib.DataCount;
			break;
		case VertexBufferDataType::INT:
			glVertexAttribIPointer(index, (GLint)attrib.DataCount, GL_INT, (GLint)m_Specification.VertexSize, (void*)offset);
			offset += sizeof(int) * attrib.DataCount;
			break;
		case VertexBufferDataType::BYTE:
			glVertexAttribIPointer(index, (GLint)attrib.DataCount, GL_BYTE, (GLint)m_Specification.VertexSize, (void*)offset);
			offset += sizeof(char) * attrib.DataCount;
			break;
		case VertexBufferDataType::UNSIGNED_INT:
			glVertexAttribIPointer(index, (GLint)attrib.DataCount, GL_UNSIGNED_INT, (GLint)m_Specification.VertexSize, (void*)offset);
			offset += sizeof(int) * attrib.DataCount;
			break;
		case VertexBufferDataType::UNSIGNED_BYTE:
			glVertexAttribIPointer(index, (GLint)attrib.DataCount, GL_UNSIGNED_BYTE, (GLint)m_Specification.VertexSize, (void*)offset);
			offset += sizeof(char) * attrib.DataCount;
			break;
		}
		index++;
	}

	UnBind();

	m_VertexArray = data;
	m_VertexCounter = (int) m_Specification.BufferSize;
	glBindVertexArray(0);

}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_VB_ID);
}


void OpenGLVertexBuffer::Bind() const
{
	glBindVertexArray(m_VAO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB_ID);
}


void OpenGLVertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}




