#pragma once
#include "../Mesh/Mesh.h"

#include "../../ECS/Components/CameraComponent.h"
#include "../../ECS/Components/TransformComponent.h"

namespace Engine {
	class Renderer {
	public:
		static void Init();
		static void Shutdown();
		
		static void BeginScene(CameraComponent& camera);
		static void EndScene();
		static void Submit(const Mesh& mesh, TransformComponent& transform);
		static void Flush();
	};
}