#pragma once

#include "EntityManager.h"

namespace Engine {
	EntityManager::EntityManager() {}
	Entity* EntityManager::CreateEntity() {
		Entity* entity = new Entity();
		entities.insert(entity);
		return entity;
	}
	void EntityManager::DestroyEntity(Entity* entity) {
		// TODO: Properly handle component cleanup (nejla zove)
	}
	void EntityManager::Update(float deltaTime) {
		for (auto& entity : entities) {
			entity->Update();
		}
	}

}