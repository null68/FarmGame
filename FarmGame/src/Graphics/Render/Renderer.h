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
		
		static void BeginScene(CameraComponent& camera);
		static void EndScene();
		static void Submit(const Mesh& mesh, TransformComponent& transform, MaterialComponent& material);
	private:
		static CameraComponent* s_ActiveCamera;
		static std::vector<std::unique_ptr<Batch>> s_Batches;
	};
}