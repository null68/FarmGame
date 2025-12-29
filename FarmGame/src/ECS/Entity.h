#pragma once

namespace Engine {
	class Entity {
	public:
		Entity() = default;
		virtual ~Entity() = default;
		void Update();
	};
}