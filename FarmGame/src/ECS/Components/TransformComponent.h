#pragma once

#include <glm.hpp>

#include "../Component.h"

namespace Engine {
	class TransformComponent : public Component {
		glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale{ 1.0f, 1.0f, 1.0f };
	};
}