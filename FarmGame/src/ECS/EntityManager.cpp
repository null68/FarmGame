#pragma once

#include "EntityManager.h"
#include "Components/ScriptComponent.h"

namespace Engine {
	EntityManager::EntityManager() {}
	Entity* EntityManager::CreateEntity() {
		Entity* entity = new Entity();
		entities.push_back(entity);
		return entity;
	}
	void EntityManager::DestroyEntity(Entity* entity) {
		std::vector<Entity*>::iterator result = std::find(entities.begin(), entities.end(), entity);
		if (result != entities.end()) {
			// TODO: ako ima ScriptComponent pozovi OnDestroy
			delete *result;
			entities.erase(result);
		}
	}
	void EntityManager::Update(float deltaTime) {
		for (Entity* entity : entities) {
			if (entity->HasComponent<ScriptComponent>()) {
				entity->GetComponent<ScriptComponent>()->OnUpdate(deltaTime);
			}
		}
	}

}