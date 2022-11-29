#pragma once

#include "Core/Core.h"

#include "Vertex.h"
#include <vector>
#include <initializer_list>

enum class VertexBufferDataType {
	FLOAT,
	INT,
	UNSIGNED_INT,
	BYTE,
	UNSIGNED_BYTE
};

struct VertexAttrib {
	VertexBufferDataType data_type;
	size_t data_count;
	VertexAttrib() = default;
};

struct VertexAttributes {
	std::vector<VertexAttrib> attributes;
	VertexAttributes(std::initializer_list<VertexAttrib> attributes) : attributes(attributes) {}
	VertexAttributes() = default;
};

struct VertexBufferSpec {
	VertexAttributes attributes;
	size_t buffer_size;
	size_t vertex_size;
	bool dynamic = false;
	VertexBufferSpec() {
		buffer_size = 0;
		vertex_size = 0;
	}
};

class VertexBuffer
{

private:

	void* m_next_vertex;
	
protected: 

	void* m_vertex_array;
	int m_vertex_counter;

	VertexBufferSpec m_specification;

	void AllocateBuffer() {
		m_vertex_array = new uint8_t[m_specification.buffer_size * m_specification.vertex_size];
		m_next_vertex = m_vertex_array;
	}

public:

	virtual ~VertexBuffer() {
		if (m_specification.dynamic)
		delete[] m_vertex_array;
	}

	VertexBuffer() {
		m_next_vertex = nullptr;
		m_vertex_array = nullptr;
		m_vertex_counter = 0;
	}

	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	bool HasCapacity() const {
		return (size_t) (m_specification.vertex_size - m_vertex_counter) < m_specification.buffer_size;
	}

	int PlaceOccupied() const {
		return (int)(m_specification.vertex_size - (m_specification.vertex_size - m_vertex_counter));
	}

	void Reset() {
		m_next_vertex = m_vertex_array;
		m_vertex_counter = 0;
	}

	template<typename T>
	void AddVertex(T v) {	
		*((T*)m_next_vertex) = v;
		T* ptr = (T*) m_next_vertex;
		ptr++;
		m_next_vertex = ptr;
		m_vertex_counter++;
	}

	void* GetVertices() const {
		return m_vertex_array;
	}

	void* GetNextVertex() const {
		return m_next_vertex;
	}

	VertexBufferSpec& GetSpec() {
		return m_specification;
	}

	static VertexBuffer* Create(const VertexBufferSpec& spec, RenderingAPI api);
	static VertexBuffer* Create(const VertexBufferSpec& spec, void* data, RenderingAPI api);

};




