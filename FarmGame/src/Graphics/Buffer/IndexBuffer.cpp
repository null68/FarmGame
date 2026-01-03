#include "IndexBuffer.h"
#include <glad/glad.h>

namespace Engine {
	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
		: m_Count(count) {
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	}
	void IndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}
	void IndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void IndexBuffer::Delete() const {
		glDeleteBuffers(1, &m_Id);
	}
}