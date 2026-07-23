#pragma once

#include "../Mesh/Mesh.h"
#include "Batch.h"

#include "../../ECS/Components/CameraComponent.h"
#include "../../ECS/Components/TransformComponent.h"
#include "../../ECS/Components/MaterialComponent.h"

namespace Engine {
	class Renderer {
	public:
		static void Init();
		static void Shutdown();
		
		static void SetViewportSize(int width, int height);

		static void BeginScene(CameraComponent& camera);
		static void EndScene();
		static void Submit(const Mesh& mesh, TransformComponent& transform, MaterialComponent& material);
	private:
		struct BatchKey {
			ShaderProgram* shader;
			const Mesh* mesh;
			const MaterialComponent* material;

			bool operator==(const BatchKey& other) const {
				return shader == other.shader && mesh == other.mesh && material == other.material;
			}
		};
		struct BatchKeyHasher {
			size_t operator()(const BatchKey& key) const {
				size_t h1 = std::hash<void*>()(static_cast<void*>(key.shader));
				size_t h2 = std::hash<const void*>()(static_cast<const void*>(key.mesh));
				size_t h3 = std::hash<const void*>()(static_cast<const void*>(key.material));
				return h1 ^ (h2 << 1) ^ (h3 << 2);
			}
		};

		static void ApplyRenderState(RenderQueue queue);

		static CameraComponent* s_ActiveCamera;
		static std::vector<std::unique_ptr<Batch>> s_Batches;
		static std::unordered_map<BatchKey, Batch*, BatchKeyHasher> s_BatchLookup;

		static int s_ViewportWidth;
		static int s_ViewportHeight;
	};
}