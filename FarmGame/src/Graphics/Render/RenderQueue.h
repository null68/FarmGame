#pragma once

namespace Engine {
	enum class RenderQueue {
		Opaque = 0,
		Skybox = 1,
		Transparent = 2,
		UI = 3
	};
}