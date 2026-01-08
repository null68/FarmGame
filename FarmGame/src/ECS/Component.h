#pragma once

namespace Engine {
	class Entity;
	class Component {
	public:
		Entity *entity = nullptr;
		virtual ~Component() = default;
	};
}