#include "ShaderProgram.h"
#include <glad/glad.h>
#include <iostream>
#include <string>

namespace Engine {
	ShaderProgram::ShaderProgram()
		: m_Id(glCreateProgram()) {
	}
	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_Id);
	}
	void ShaderProgram::AttachVertex(const char* vertexSource) {
		m_VertexShaderId = glCreateShader(GL_VERTEX_SHADER);

		int success;

		glShaderSource(m_VertexShaderId, 1, &vertexSource, nullptr);
		glCompileShader(m_VertexShaderId);


		glGetShaderiv(m_VertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(m_VertexShaderId, 512, nullptr, infoLog);
			throw std::runtime_error(std::string("Vertex shader compilation failed: ") + infoLog);
		} 
		glAttachShader(m_Id, m_VertexShaderId);
	}
	void ShaderProgram::AttachFragment(const char* fragmentSource) {
		m_FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		int success;

		glShaderSource(m_FragmentShaderId, 1, &fragmentSource, nullptr);
		glCompileShader(m_FragmentShaderId);


		glGetShaderiv(m_FragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(m_FragmentShaderId, 512, nullptr, infoLog);
			throw std::runtime_error(std::string("Fragment shader compilation failed: ") + infoLog);
		}
		glAttachShader(m_Id, m_FragmentShaderId);
	}
	void ShaderProgram::Link() {
		int success;

		glLinkProgram(m_Id);

		glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(m_Id, 512, nullptr, infoLog);
			throw std::runtime_error(std::string("Shader program linking failed: ") + infoLog);
		} // todo: ne znam da li je ovo najpametnije error handlovanje, istraziti

		// shaderi su linkovi za program ne trebaju vise
		glDeleteShader(m_VertexShaderId);
		glDeleteShader(m_FragmentShaderId);
	}

	void ShaderProgram::Bind() const {
		glUseProgram(m_Id);
	}
	// realno i nepotrebno jer jedan shader replaceuje drugi al ajd
	void ShaderProgram::Unbind() const {
		glUseProgram(0);
	}

	int ShaderProgram::GetUniformLocation(const char* name) const {
		auto it = m_UniformLocationCache.find(name);
		if (it != m_UniformLocationCache.end())
			return it->second;

		int location = glGetUniformLocation(m_Id, name);

		m_UniformLocationCache[name] = location;
		return location;
	}

	void ShaderProgram::SetUniform1i(const char* name, int value) const {
		glUniform1i(GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform1f(const char* name, float value) const {
		glUniform1f(GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform1b(const char* name, bool value) const {
		glUniform1i(GetUniformLocation(name), value ? 1 : 0);
	}

	void ShaderProgram::SetUniformVec2f(const char* name, const glm::vec2& vec) const {
		glUniform2f(GetUniformLocation(name), vec.x, vec.y);
	}

	void ShaderProgram::SetUniformVec3f(const char* name, const glm::vec3& vec) const {
		glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
	}

	void ShaderProgram::SetUniformVec4f(const char* name, const glm::vec4& vec) const {
		glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void ShaderProgram::SetUniformMat4f(const char* name, const glm::mat4& mat) const {
		glUniformMatrix4fv(
			GetUniformLocation(name),
			1,
			GL_FALSE,
			glm::value_ptr(mat)
		);
	}

}
	