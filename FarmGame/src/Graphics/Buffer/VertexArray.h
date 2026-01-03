#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Engine {
	class VertexArray {
	private:
		unsigned int m_Id;
	public:
		VertexArray();
		void SetLayout(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer) const;
		void Bind() const;
		void Unbind() const;
		void Delete() const;
	};
}