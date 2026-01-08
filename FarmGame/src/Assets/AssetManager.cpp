#include <iostream>
#include <fstream>
#include <string>
#include "AssetManager.h"

namespace Engine {
	const char* AssetManager::LoadShaderFile(const char* filePath) {
		std::string shaderCode;

		std::ifstream shaderFile(filePath);
		if (shaderFile.is_open()) {
			std::string line;
			while (std::getline(shaderFile, line)) {
				shaderCode += line + "\n";
			}
			shaderFile.close();
		}
		else {
			std::cerr << "Failed to open shader file: " << filePath << std::endl;
			return nullptr;
		}
		char* shaderCodeCStr = new char[shaderCode.size() + 1];
		strcpy_s(shaderCodeCStr, shaderCode.size() + 1, shaderCode.c_str());
		return shaderCodeCStr;
	}
}