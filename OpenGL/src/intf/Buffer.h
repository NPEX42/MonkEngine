#pragma once

#include "glad/glad.h"
#include <vector>
#include <stdint.h>

namespace gl {
	class VertexBuffer {
	private:
		std::vector<float> m_data;
		uint32_t m_id;

	public:
		VertexBuffer();

		void bind() {
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}

		void unbind() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void setData(float* data, size_t size);

		void setAttributes(size_t index, size_t element_size, uint32_t type, GLboolean normalised, size_t size, void* offset);
	};



	class VAO {
	private:
		uint32_t m_id;

	public:
		VAO() : m_id(0) {
			glGenVertexArrays(1, &m_id);
		}

		void bind() {
			glBindVertexArray(m_id);
		}

		void unbind() {
			glBindVertexArray(0);
		}

	};


	class EBO {
	private:
		uint32_t m_id;
		uint32_t* m_data;
		size_t m_size;
	public:
		EBO() : m_id(0), m_data(NULL), m_size(0) {
			glGenBuffers(1, &m_id);
		}

		void bind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		}

		void unbind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void setTriangles(uint32_t* tris, size_t size) {
			m_data = tris;
			m_size = size;

			bind();

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, m_data, GL_STATIC_DRAW);
		}

		size_t size() {
			return m_size;
		}

	};
}