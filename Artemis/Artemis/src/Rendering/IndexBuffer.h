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

class IndexBuffer {

private:

	IndexBufferType m_index_buffer_type = IndexBufferType::UNSIGNED_INT;
	uint32_t m_type_size = 0;
	uint32_t m_indicies_count = 0;

	void* m_data = nullptr;

public:

	IndexBuffer() = default;
	~IndexBuffer() {
		delete[] m_data;
	}

	IndexBuffer(IndexBuffer&) = delete;
	IndexBuffer& operator=(IndexBuffer& other) = delete;

	template<typename T>
	void SetData(IndexBufferType data_type, T* data, uint32_t data_size) {
		m_type_size = sizeof(T);
		m_indicies_count = data_size / m_type_size;
		m_index_buffer_type = data_type;
		m_data = new uint8_t[data_size];
		memcpy(m_data, data, data_size);
	}

	const void* GetDataPointer() const {
		return m_data;
	}

	uint32_t GetIndiciesCount() const {
		return m_indicies_count;
	}

	IndexBufferType GetType() const {
		return m_index_buffer_type;
	}

};
