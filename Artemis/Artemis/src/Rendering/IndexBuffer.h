#pragma once

#include "Core/Core.h"
#include <vector>
#include <utility>

enum class IndexBufferType {
	UNSIGNED_INT, 
	INT,
	UNSIGNED_SHORT,
	SHORT,
	UNSIGNED_CHAR, 
	CHAR
};

template<typename T>
struct IndexTriangle {

	T index_0;
	T index_1;
	T index_2;

};

template<typename T>
struct IndexBufferSpecification {

	IndexBufferType type;
	std::vector<IndexTriangle<T>> triangles;

};

template<typename T>
class IndexBuffer {

private:

	IndexBufferSpecification<T> m_specification;

public:

	IndexBuffer(IndexBufferSpecification<T>&& spec) {
		m_specification = std::move(spec);
	}


	T* GetDataPointer() {
		return (T*) m_specification.triangles.data();
	}


};
