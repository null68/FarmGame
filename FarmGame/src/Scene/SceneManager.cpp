#include "SceneManager.h"

namespace Engine {
	SceneManager& SceneManager::GetInstance() {
		static SceneManager instance;
		return instance;
	}
	
	Scene* SceneManager::CreateScene(const char* name) {
		if (m_Scenes.find(name) != m_Scenes.end()) {
			std::cerr << "Scene with name " << name << " already exists. Returning existing scene." << std::endl;
			return m_Scenes[name];
		}
		Scene* newScene = new Scene(name);
		m_Scenes[name] = newScene;
		return newScene;
	}

	Scene* SceneManager::LoadScene(const char* name) {
		auto it = m_Scenes.find(name);
		if (it != m_Scenes.end()) {
			m_ActiveScene = it->second;
			m_ActiveScene->m_IsLoaded = true;
			return m_ActiveScene;
		}
		std::cerr << "Scene with name " << name << " does not exist. Cannot load scene." << std::endl;
		return nullptr;
	}

	void SceneManager::UnloadScene(const char* name) {
		auto it = m_Scenes.find(name);
		if (it != m_Scenes.end()) {
			it->second->m_IsLoaded = false;
			if (m_ActiveScene == it->second) {
				m_ActiveScene = nullptr;
			}
		}
		else {
			std::cerr << "Scene with name " << name << " does not exist. Cannot unload scene." << std::endl;
		}
	}
	
	void SceneManager::DeleteScene(const char* name) {
		auto it = m_Scenes.find(name);
		if (it != m_Scenes.end()) {
			delete it->second;
			m_Scenes.erase(it);
			if (m_ActiveScene && strcmp(m_ActiveScene->m_Name, name) == 0) {
				m_ActiveScene = nullptr;
			}
		}
		else {
			std::cerr << "Scene with name " << name << " does not exist. Cannot delete scene." << std::endl;
		}
	}
}