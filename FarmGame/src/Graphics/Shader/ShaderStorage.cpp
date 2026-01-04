#include "ShaderStorage.h"

namespace Engine {
	static ShaderStorage& GetInstance() {
		// cudno ali ovako treba (java dev sam :/)
		static ShaderStorage instance;
		return instance;
	}
	// TODO: dodati da vertexShaderName i fragmentShaderName bude path do filea, poceti AssetManager radit
	std::shared_ptr<ShaderProgram> ShaderStorage::Load(std::string name, std::string vertexShaderName, std::string fragmentShaderName) {
		if (Exists(name))
			return m_Shaders[name];

		auto shader = std::make_shared<ShaderProgram>();
		shader->AttachVertex(vertexShaderName.c_str());
		shader->AttachFragment(fragmentShaderName.c_str());
		shader->Link();
		m_Shaders[name] = shader;
		return shader;
	}
	std::shared_ptr<ShaderProgram> ShaderStorage::Get(std::string name)
	{
		if (Exists(name))
			return m_Shaders[name];

		throw std::runtime_error("Shader with name " + name + " does not exist in storage.");
	}
	bool ShaderStorage::Exists(const std::string& name) const {
		return m_Shaders.find(name) != m_Shaders.end();
	}
}