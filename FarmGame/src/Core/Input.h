#pragma once

#include <GLFW/glfw3.h>

namespace Engine
{
	class Input
	{
	public:
		Input(GLFWwindow* window);
		virtual ~Input();
		bool IsKeyPressed(int keycode);
		bool IsMouseButtonPressed(int button);
		void GetMousePosition(double& xpos, double& ypos);
		void SetMousePosition(double xpos, double ypos);
		void SetMouseVisible(bool visible);

		static Input* Get() { return s_Instance; }
	private:
		GLFWwindow* m_Window;
		static Input* s_Instance;
	};
}