#pragma once

#include "EntityManager.h"

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
			entities.erase(result);
			delete* result;
		}
	}
	void EntityManager::Update(float deltaTime) {
		for (Entity* entity : entities) {
			entity->Update();
		}
	}

}