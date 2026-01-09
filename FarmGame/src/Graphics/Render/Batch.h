#pragma once

#include "../Mesh/Mesh.h"
#include "../Shader/ShaderProgram.h"

#include "../../ECS/Components/CameraComponent.h"
#include "../../ECS/Components/TransformComponent.h"
#include "../../ECS/Components/MaterialComponent.h"

namespace Engine {
	class Batch {
	public:
		Batch(ShaderProgram* shader);
		~Batch();
		void Begin();
		void Submit(const Mesh& mesh, const TransformComponent& transform, const MaterialComponent& material);
		void End();
		void Flush();

		bool IsFull() const;

		void SetMesh(const Mesh* mesh) { m_Mesh = mesh; }
		void SetMaterial(const MaterialComponent* material) { m_Material = material; }

		const Mesh* GetMesh() const { return m_Mesh; }
		const MaterialComponent* GetMaterial() const { return m_Material; }
		inline ShaderProgram* GetShader() const { return m_Shader; }
	private:
		ShaderProgram* m_Shader;
		const Mesh* m_Mesh = nullptr;
		const MaterialComponent* m_Material = nullptr;

		std::vector<glm::mat4> m_Transforms;
	};
}