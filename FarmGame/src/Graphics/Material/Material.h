#pragma once

#include "../Shader/ShaderProgram.h"

namespace Engine {
	class Material {
	public:
		ShaderProgram* m_Shader = nullptr;
		// Texture* texture = nullptr; kad napravim :D
	};
}