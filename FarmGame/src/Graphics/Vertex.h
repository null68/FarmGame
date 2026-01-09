#pragma once

#include <glm.hpp>

namespace Engine {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;

		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 tex_coord) : Position(position), Normal(normal), TexCoord(tex_coord) {}
		Vertex(glm::vec3 position, glm::vec3 normal) : Position(position), Normal(normal), TexCoord(glm::vec2(0.0f)) {}
		Vertex(glm::vec3 position) : Position(position), Normal(glm::vec3(0.0f)), TexCoord(glm::vec2(0.0f)) {}
		Vertex() : Position(glm::vec3(0.0f)), Normal(glm::vec3(0.0f)), TexCoord(glm::vec2(0.0f)) {}
	};
}