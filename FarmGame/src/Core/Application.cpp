#include <iostream>
#include "Application.h"

namespace Engine {
	Application::Application() {
		Window = std::make_unique<Engine::Window>(800, 600, "Farm Game");
	}
	void Application::Run() {
		while (!Window->ShouldClose()) {
			Window->PollEvents();

			Time::Update();
			std::cout << Time::DeltaTime() << std::endl;

			Window->SwapBuffers();
		}
	}
}