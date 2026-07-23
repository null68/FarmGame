#include "Mesh.h"
#include <glad/glad.h>


namespace Engine {
	Mesh::Mesh(const MeshData& data)
        :  
        m_VBO(data.vertices.data(), static_cast<unsigned int>(data.vertices.size() * sizeof(Vertex))),
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

    void Mesh::ConfigureInstanceBuffer(unsigned int instanceVBO) const {
        m_VAO.Bind();
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

        const size_t vec4Size = sizeof(glm::vec4);
        for (int i = 0; i < 4; i++) {
            glEnableVertexAttribArray(3 + i);
            glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * vec4Size));
            glVertexAttribDivisor(3 + i, 1);
        }

        m_VAO.Unbind();
    }
}