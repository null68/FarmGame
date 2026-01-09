#pragma once

#include "../Component.h"

namespace Engine {
	class MaterialComponent : public Component {
	public:
		std::shared_ptr<ShaderProgram> shader;
	};
}