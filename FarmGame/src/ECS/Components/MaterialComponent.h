#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <glm.hpp>

#include "../Component.h"
#include "../../Graphics/Shader/ShaderProgram.h"
#include "../../Graphics/Texture/Texture.h"
#include "../../Graphics/Render/RenderQueue.h"

namespace Engine {
	using UniformValue = std::variant<int, float, bool, glm::vec2, glm::vec3, glm::vec4, glm::mat4>;

	class MaterialComponent : public Component {
	public:
		std::shared_ptr<ShaderProgram> shader;
		RenderQueue queue = RenderQueue::Opaque;

		std::shared_ptr<Texture> texture;
		unsigned int textureSlot = 0;

		void SetUniform(const std::string& name, UniformValue value) {
			m_Uniforms[name] = std::move(value);
		}

		void Bind(ShaderProgram& shaderRef) const {

			shaderRef.SetUniformVec4f("u_Color", glm::vec4(1.0f));
			shaderRef.SetUniform1b("u_UseTexture", texture != nullptr && texture->IsValid());

			if (texture && texture->IsValid()) {
				texture->Bind(textureSlot);
				shaderRef.SetUniform1i("u_Texture", static_cast<int>(textureSlot));
			}

			for (const auto& [name, value] : m_Uniforms) {
				std::visit([&](auto&& v) {
					using T = std::decay_t<decltype(v)>;
					if constexpr (std::is_same_v<T, int>)         shaderRef.SetUniform1i(name.c_str(), v);
					else if constexpr (std::is_same_v<T, float>)  shaderRef.SetUniform1f(name.c_str(), v);
					else if constexpr (std::is_same_v<T, bool>)   shaderRef.SetUniform1b(name.c_str(), v);
					else if constexpr (std::is_same_v<T, glm::vec2>) shaderRef.SetUniformVec2f(name.c_str(), v);
					else if constexpr (std::is_same_v<T, glm::vec3>) shaderRef.SetUniformVec3f(name.c_str(), v);
					else if constexpr (std::is_same_v<T, glm::vec4>) shaderRef.SetUniformVec4f(name.c_str(), v);
					else if constexpr (std::is_same_v<T, glm::mat4>) shaderRef.SetUniformMat4f(name.c_str(), v);
					}, value);
			}
		}

	private:
		std::unordered_map<std::string, UniformValue> m_Uniforms;
	};
}
