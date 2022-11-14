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
	VertexBufferDataType DataType;
	size_t DataCount;
	VertexAttrib() = default;
};

struct VertexAttributes {
	std::vector<VertexAttrib> Attributes;
	VertexAttributes(std::initializer_list<VertexAttrib> attributes) : Attributes(attributes) {}
	VertexAttributes() = default;
};

struct VertexBufferSpec {
	VertexAttributes Attributes;
	size_t BufferSize;
	size_t VertexSize;
	bool Dynamic = false;
	VertexBufferSpec() {
		BufferSize = 0;
		VertexSize = 0;
	}
};

class VertexBuffer
{

private:

	void* m_NextVertex;
	
protected: 

	void* m_VertexArray;
	int m_VertexCounter;

	VertexBufferSpec m_Specification;

	void AllocateBuffer() {
		m_VertexArray = new char[m_Specification.BufferSize * m_Specification.VertexSize];
		m_NextVertex = m_VertexArray;
	}

public:

	virtual ~VertexBuffer() {
		if (m_Specification.Dynamic)
		delete[] m_VertexArray;
	}

	VertexBuffer() {
		m_NextVertex = nullptr;
		m_VertexArray = nullptr;
		m_VertexCounter = 0;
	}

	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	bool HasCapacity() const {
		return (size_t) (m_Specification.VertexSize - m_VertexCounter) < m_Specification.BufferSize;
	}

	int PlaceOccupied() const {
		return (int)(m_Specification.VertexSize - (m_Specification.VertexSize - m_VertexCounter));
	}

	void Reset() {
		m_NextVertex = m_VertexArray;
		m_VertexCounter = 0;
	}

	template<typename T>
	void AddVertex(T v) {	
		*((T*)m_NextVertex) = v;
		T* ptr = (T*) m_NextVertex;
		ptr++;
		m_NextVertex = ptr;
		m_VertexCounter++;
	}

	void* GetVertices() const {
		return m_VertexArray;
	}

	void* GetNextVertex() const {
		return m_NextVertex;
	}

	VertexBufferSpec& GetSpec() {
		return m_Specification;
	}

	static VertexBuffer* Create(const VertexBufferSpec& spec);
	static VertexBuffer* Create(const VertexBufferSpec& spec, void* data);

};




