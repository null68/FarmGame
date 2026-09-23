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
	private:
		std::unique_ptr<Window> Window;
		std::unique_ptr<Input> Input;
	};
}

