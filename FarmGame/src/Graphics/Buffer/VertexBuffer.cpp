#include "VertexBuffer.h"
#include <glad/glad.h>

namespace Engine {
	VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	void VertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}
	void VertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VertexBuffer::Delete() const {
		glDeleteBuffers(1, &m_Id);
	}
}