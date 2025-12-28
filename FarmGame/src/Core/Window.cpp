#include <iostream>
#include "Window.h"

namespace Engine {
	Window::Window(int width, int height, const char* title)
		: m_Width(width), m_Height(height), m_Title(title) {
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW"); // dok ne skontam sta cu drugo ma da i ovo je ok
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
		
		if(!m_Window) {
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window"); // isto tako
		}

		glfwMakeContextCurrent(m_Window);
	}

	Window::~Window() {
		if (m_Window) {
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}

		glfwTerminate();
	}

	bool Window::ShouldClose() const {
		return glfwWindowShouldClose(m_Window);
	}

	void Window::PollEvents() const {
		glfwPollEvents();
	}

	void Window::SwapBuffers() const {
		glfwSwapBuffers(m_Window);
	}
}