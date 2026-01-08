#pragma once

#include "../Component.h"
#include "../../Graphics/Mesh/Mesh.h"


namespace Engine {
	class MeshComponent : public Component {
		std::shared_ptr<Mesh> mesh;
	};
}