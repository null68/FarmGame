#pragma once

#include "../Component.h"
#include "../../Graphics/Mesh/Mesh.h"


namespace Engine {
	class MeshComponent : public Component {
	public:
		std::shared_ptr<Mesh> mesh;
	};
}