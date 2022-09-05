#include "Buffer.h"

namespace gl {

	VertexBuffer::VertexBuffer() : m_data(std::vector<float>()), m_id(0) {
		glGenBuffers(1, &m_id);
		bind();
	}

	void VertexBuffer::setData(float* data, size_t size)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, size, (void*) data, GL_STATIC_DRAW);
	}

	void VertexBuffer::setAttributes(size_t index, size_t size, uint32_t type, GLboolean normalised, size_t stride, void* offset)
	{
		bind();
		glVertexAttribPointer(index, size, type, normalised, stride, (const void*) offset);
		glEnableVertexAttribArray(index);
	}



}