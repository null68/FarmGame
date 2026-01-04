#pragma once

#include <iostream>
#include <unordered_map>
#include "ShaderProgram.h"

namespace Engine {
	class ShaderStorage {
	public:
		static ShaderStorage& GetInstance();

		std::shared_ptr<ShaderProgram> Load(std::string name, std::string vertexShaderName, std::string fragmentShaderName);
		std::shared_ptr<ShaderProgram> Get(std::string name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_Shaders;
	};
}