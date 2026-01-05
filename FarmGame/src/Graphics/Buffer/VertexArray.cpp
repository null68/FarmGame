#include <glad/glad.h>
#include "VertexArray.h"
#include "../Vertex.h"

namespace Engine {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_Id);
		Bind();
	}
	void VertexArray::SetLayout(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer) const {
		Bind();
		vertexBuffer.Bind();
		indexBuffer.Bind();

		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(0);
		// normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(1);
		// tex coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
		glEnableVertexAttribArray(2);
	}
	void VertexArray::Bind() const {
		glBindVertexArray(m_Id);
	}
	void VertexArray::Unbind() const {
		glBindVertexArray(0);
	}
	void VertexArray::Delete() const {
		glDeleteVertexArrays(1, &m_Id);
	}
}