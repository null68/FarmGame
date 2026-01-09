#pragma once

#include <iostream>
#include "Window.h"
#include "Time.h"
#include "Input.h"
#include "../Graphics/Mesh/MeshData.h"

namespace Engine {
	class Application {
	public:
		Application();
		virtual ~Application() = default;
		void Run();

		MeshData CreateCube();
	private:
		// dodat unique_ptr's za window, renderer, input manager, scene manager, itd.
		std::unique_ptr<Window> Window;
		std::unique_ptr<Input> Input;
	};
}

