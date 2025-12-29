#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

namespace Engine {
	class Window {
		public:
			Window(int width, int height, const char* title);
			virtual ~Window();
			bool ShouldClose() const;
			void PollEvents() const;
			void SwapBuffers() const;

			GLFWwindow* GetNativeWindow() const { return m_Window; }
		private:
			int m_Width;
			int m_Height;
			const char* m_Title;
			GLFWwindow* m_Window; 
	};
}

