#pragma once

#include <iostream>
#include "../Vertex.h"

namespace Engine {
	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices; // mozda prebaciti na size_t?
	};
}