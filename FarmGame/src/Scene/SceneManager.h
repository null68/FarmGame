#pragma once

#include <unordered_map>

#include "Scene.h"

namespace Engine {
	class SceneManager {
	private:
		Scene* m_ActiveScene = nullptr;
	public:
		std::unordered_map<const char*, Scene*> m_Scenes;

		static SceneManager& GetInstance();
		Scene* CreateScene(const char* name);
		Scene* LoadScene(const char* name);
		Scene* GetActiveScene() const { return m_ActiveScene; }
		void UnloadScene(const char* name);
		void DeleteScene(const char* name);
	};
}