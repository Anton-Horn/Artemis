
#include "OpenGLVertexBuffer.h"


#include "Core\Log.h"
#include "glad\glad.h"



OpenGLVertexBuffer::OpenGLVertexBuffer(const VertexBufferSpec& spec)
{
	m_specification = spec;
	m_specification.dynamic = true;

	glGenVertexArrays(1, &m_vao_id);
	glBindVertexArray(m_vao_id);

	glGenBuffers(1, &m_vb_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vb_id);
	glBufferData(GL_ARRAY_BUFFER, spec.buffer_size * m_specification.vertex_size, nullptr, GL_DYNAMIC_DRAW);

	int index = 0;
	size_t offset = 0;
	for (auto& attrib : m_specification.attributes.attributes) {
		glEnableVertexAttribArray(index);
		switch (attrib.data_type) {
		case VertexBufferDataType::FLOAT:
			glVertexAttribPointer(index, (GLint)attrib.data_count, GL_FLOAT, GL_FALSE, (GLsizei)m_specification.vertex_size, (void*) offset);
			offset += (int) sizeof(float) * attrib.data_count;
			break;
		case VertexBufferDataType::INT:
			glVertexAttribIPointer(index, (GLint)attrib.data_count, GL_INT, (GLsizei) m_specification.vertex_size, (void*)offset);
			offset += (int) sizeof(int) * attrib.data_count;
			break;
		case VertexBufferDataType::BYTE:
			glVertexAttribIPointer(index, (GLint)attrib.data_count, GL_BYTE, (GLsizei)m_specification.vertex_size, (void*)offset);
			offset += (int) sizeof(char) * attrib.data_count;
			break;
		case VertexBufferDataType::UNSIGNED_INT:
			glVertexAttribIPointer(index, (GLint)attrib.data_count, GL_UNSIGNED_INT, (GLsizei)m_specification.vertex_size, (void*)offset);
			offset += (int) sizeof(int) * attrib.data_count;
			break;
		case VertexBufferDataType::UNSIGNED_BYTE:
			glVertexAttribIPointer(index, (GLint)attrib.data_count, GL_UNSIGNED_BYTE, (GLsizei)m_specification.vertex_size, (void*)offset);
			offset += (int) sizeof(char) * attrib.data_count;
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
	m_specification = spec;
	m_specification.dynamic = false;

	glGenVertexArrays(1, &m_vao_id);
	glBindVertexArray(m_vao_id);
	
	glGenBuffers(1, &m_vb_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vb_id);
	glBufferData(GL_ARRAY_BUFFER, m_specification.buffer_size * m_specification.vertex_size, data, GL_STATIC_DRAW);

	int index = 0;
	size_t offset = 0;
	for (auto& attrib : m_specification.attributes.attributes) {
		glEnableVertexAttribArray(index);
		switch (attrib.data_type) {
		case VertexBufferDataType::FLOAT:
			glVertexAttribPointer(index, (GLint) attrib.data_count, GL_FLOAT, GL_FALSE, (GLint)m_specification.vertex_size, (void*)offset);
			offset += sizeof(float) * attrib.data_count;
			break;
		case VertexBufferDataType::INT:
			glVertexAttribIPointer(index, (GLint)attrib.data_count, GL_INT, (GLint)m_specification.vertex_size, (void*)offset);
			offset += sizeof(int) * attrib.data_count;
			break;
		case VertexBufferDataType::BYTE:
			glVertexAttribIPointer(index, (GLint)attrib.data_count, GL_BYTE, (GLint)m_specification.vertex_size, (void*)offset);
			offset += sizeof(char) * attrib.data_count;
			break;
		case VertexBufferDataType::UNSIGNED_INT:
			glVertexAttribIPointer(index, (GLint)attrib.data_count, GL_UNSIGNED_INT, (GLint)m_specification.vertex_size, (void*)offset);
			offset += sizeof(int) * attrib.data_count;
			break;
		case VertexBufferDataType::UNSIGNED_BYTE:
			glVertexAttribIPointer(index, (GLint)attrib.data_count, GL_UNSIGNED_BYTE, (GLint)m_specification.vertex_size, (void*)offset);
			offset += sizeof(char) * attrib.data_count;
			break;
		}
		index++;
	}
	
	UnBind();

	m_vertex_array = data;
	m_vertex_counter = (int) m_specification.buffer_size;
	
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_vb_id);
	glDeleteVertexArrays(1, &m_vao_id);
}


void OpenGLVertexBuffer::Bind() const
{
	glBindVertexArray(m_vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vb_id);
}


void OpenGLVertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}




