#include "Time.h"

namespace Engine {
	float Time::s_DeltaTime = 0.0f;

	float Time::DeltaTime() {
		return s_DeltaTime;
	}

	void Time::Update() {
		static double lastTime = 0.0;
		double currentTime = glfwGetTime();
		s_DeltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;
	}
}