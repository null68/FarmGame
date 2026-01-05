#pragma once

#include "MeshData.h"
#include "../Buffer/IndexBuffer.h"
#include "../Buffer/VertexArray.h"
#include "../Buffer/VertexBuffer.h"

namespace Engine {
	class Mesh {
	public:
		Mesh(const MeshData& data);
		void Bind() const;
		void Unbind() const;
		
		uint32_t GetIndexCount() const { return m_IndexCount; }
		uint32_t GetVertexCount() const { return m_VertexCount; }
	private:
		VertexArray m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer m_IBO;

		uint32_t m_IndexCount;
		uint32_t m_VertexCount;
	};
}