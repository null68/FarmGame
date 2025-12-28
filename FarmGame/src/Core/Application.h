#pragma once

#include <iostream>
#include "Window.h"
#include "Time.h"

namespace Engine {
	class Application {
		public:
			Application();
			virtual ~Application() = default;
			void Run();
		private:
			// dodat unique_ptr's za window, renderer, input manager, scene manager, itd.
			std::unique_ptr<Window> Window;
	};
}

