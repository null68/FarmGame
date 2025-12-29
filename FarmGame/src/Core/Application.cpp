#include <iostream>
#include "Application.h"

namespace Engine {
	Application::Application() {
		Window = std::make_unique<Engine::Window>(800, 600, "Farm Game");
		Input = std::make_unique<Engine::Input>(Window->GetNativeWindow());
	}
	void Application::Run() {
		while (!Window->ShouldClose()) {
			Window->PollEvents();

			Time::Update();

			if (Input->IsKeyPressed(GLFW_KEY_ESCAPE)) {
				std::cout << "Escape key pressed. Exiting application." << std::endl;
				break;
			}

			Window->SwapBuffers();
		}
	}
}