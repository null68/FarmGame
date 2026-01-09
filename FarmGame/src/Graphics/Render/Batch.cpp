#include "Batch.h"

#include <glad/glad.h>

namespace Engine {
	Batch::Batch(ShaderProgram* shader)
		: m_Shader(shader) {
	}
	Batch::~Batch() {
	}
    void Batch::Begin()
    {
        m_Transforms.clear();
        m_Mesh = nullptr;
        m_Material = nullptr;
        m_Shader->Bind();
    }

    void Batch::Submit(const Mesh& mesh, const TransformComponent& transform, const MaterialComponent& material) {
        if (!m_Mesh)
            m_Mesh = &mesh;
        if (!m_Material)
            m_Material = &material;

        m_Transforms.push_back(transform.GetModelMatrix());
    }

    void Batch::End()
    {
        // nista za sad
    }

    void Batch::Flush()
    {
        if (!m_Mesh || m_Transforms.empty())
            return;

        m_Mesh->Bind();
        // m_Material->Bind(*m_Shader); 

        for (size_t i = 0; i < m_Transforms.size(); i++)
        {
            m_Shader->SetUniformMat4f("u_Model", m_Transforms[i]);
            glDrawElements(GL_TRIANGLES, m_Mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
        }

        m_Transforms.clear();
    }

    bool Batch::IsFull() const
    {
        return false; // ne pravim limit i End() method jer ovo nije pravi batching/instancing kada budem trebao performanse napravit cu
    }
}