#pragma once

#include "Entity.h"

namespace Engine {
	class Component {
	public:
		Entity* entity = nullptr;
		virtual ~Component() = default;
	};
}