#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "../Component.h"

namespace Engine {
	class CameraComponent : public Component {
	public:
		glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Forward{ 0.0f, 0.0f, -1.0f };
		glm::vec3 Up{ 0.0f, 1.0f, 0.0f };
		float FOV = 60.0f;
		float AspectRatio = 16.0f / 9.0f;
		float NearPlane = 0.1f;
		float FarPlane = 1000.0f;

		glm::mat4 GetViewMatrix() const {
			return glm::lookAt(Position, Position + Forward, Up);
		}

		glm::mat4 GetProjectionMatrix() const {
			return glm::perspective(glm::radians(FOV), AspectRatio, NearPlane, FarPlane);
		}

		void SetPosition(const glm::vec3& position) {
			Position = position;
		}

		void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
			FOV = fov;
			AspectRatio = aspectRatio;
			NearPlane = nearPlane;
			FarPlane = farPlane;
		}

		void LookAt(const glm::vec3& target, const glm::vec3& worldUp = glm::vec3(0.0f, 1.0f, 0.0f)) {
			Forward = glm::normalize(target - Position);
			glm::vec3 right = glm::normalize(glm::cross(Forward, worldUp));
			Up = glm::cross(right, Forward);
		}
	};
}