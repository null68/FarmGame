#pragma once

namespace Engine {
	struct CameraComponent {
		float FOV = 45.0f;
		float NearClip = 0.1f;
		float FarClip = 100.0f;
	};
}