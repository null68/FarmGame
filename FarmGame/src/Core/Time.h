#pragma once

#include <GLFW/glfw3.h>

namespace Engine {
	class Time {
	public:
		static float DeltaTime();
		static void Update();
	private:
		static float s_DeltaTime;
	};
}