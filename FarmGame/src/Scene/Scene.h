#pragma once

#include "../ECS/EntityManager.h"
#include "../ECS/Components/CameraComponent.h"

namespace Engine {
	class Scene {
	public:
		const char* m_Name = nullptr;
		bool m_IsLoaded = false;
		EntityManager* m_EntityManager;

		Scene(const char* name);
		~Scene();

		CameraComponent* GetMainCamera() const;

		// Scene Manager svakako nece dopustati vise istoimenih Scena tako da je ovo dovoljno		
		bool operator==(Scene& scene) {
			if (strcmp(m_Name, scene.m_Name) == 0)
				return true;
		}

		bool operator!=(Scene& scene) {
			return !(*this == scene);
		}
	};
}