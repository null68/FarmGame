#pragma once

#include <unordered_map>
#include <tiny_gltf_v3.h>

namespace Engine {
		class AssetManager {
	public:
		static const char* LoadShaderFile(const char* filePath);
		static bool LoadGLTFModel(const std::string& filePath, tg3_model& model);
	};
}