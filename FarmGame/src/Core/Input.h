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
	private:
		GLFWwindow* m_Window;
	};
}