#include "Mesh.h"


namespace Engine {
	Mesh::Mesh(const MeshData& data)
        :  
        m_VBO(data.vertices.data(), data.vertices.size() * sizeof(Vertex)),
		m_IBO(data.indices.data(), static_cast<unsigned int>(data.indices.size())),
        m_VertexCount(static_cast<uint32_t>(data.vertices.size())),
        m_IndexCount(static_cast<uint32_t>(data.indices.size()))
    {
        m_VAO.Bind();
		m_VAO.SetLayout(m_VBO, m_IBO);
		m_VAO.Unbind();
    }

    void Mesh::Bind() const {
        m_VAO.Bind();
	}

    void Mesh::Unbind() const {
        m_VAO.Unbind();
    }
}