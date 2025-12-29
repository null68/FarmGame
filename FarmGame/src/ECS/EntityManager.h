#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>

#include "Entity.h"


namespace Engine {
	class EntityManager {
	public:
		EntityManager();
		~EntityManager() = default;
		Entity* CreateEntity();
		void DestroyEntity(Entity* entity);
		void Update(float deltaTime);
	private:
		std::unordered_set<Entity*> entities;
	};
}