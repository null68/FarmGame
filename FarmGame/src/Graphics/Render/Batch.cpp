#include "Batch.h"
#include <glad/glad.h>

namespace Engine {
	Batch::Batch(ShaderProgram* shader)
		: m_Shader(shader) {
	}
	Batch::~Batch() {
		if (m_InstanceVBO) glDeleteBuffers(1, &m_InstanceVBO);
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

	void Batch::UploadInstanceBuffer() {
		if (m_InstanceVBO == 0) {
			glGenBuffers(1, &m_InstanceVBO);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_InstanceVBO);
		glBufferData(GL_ARRAY_BUFFER, m_Transforms.size() * sizeof(glm::mat4), m_Transforms.data(), GL_DYNAMIC_DRAW);
	}

	void Batch::Flush(const glm::mat4& view, const glm::mat4& projection)
	{
		if (!HasContent())
			return;

		UploadInstanceBuffer();

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_View", view);
		m_Shader->SetUniformMat4f("u_Projection", projection);

		m_Material->Bind(*m_Shader);

		m_Mesh->Bind();
		m_Mesh->ConfigureInstanceBuffer(m_InstanceVBO); 

		glDrawElementsInstanced(
			GL_TRIANGLES,
			m_Mesh->GetIndexCount(),
			GL_UNSIGNED_INT,
			nullptr,
			static_cast<GLsizei>(m_Transforms.size())
		);

		m_Transforms.clear();
	}


}
