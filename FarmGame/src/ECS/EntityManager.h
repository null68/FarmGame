#pragma once

#include <iostream>
#include <vector>

#include "Entity.h"


namespace Engine {
	class EntityManager {
	public:
		EntityManager();
		~EntityManager() = default;
		Entity* CreateEntity();
		void DestroyEntity(Entity* entity);
		void Update(float deltaTime);
		void Clear();
	private:
		std::vector<Entity*> entities;
	};
}