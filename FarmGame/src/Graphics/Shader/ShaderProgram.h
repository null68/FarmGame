#pragma once

// TBA: glUniforms za shader variables, cacheovanje uniformi, unordered_map mozda

namespace Engine {
	class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();
		void AttachVertex(const char* vertexSource);
		void AttachFragment(const char* fragmentSource);
		void Link();
		void Bind() const;
		void Unbind() const;
	private:
		unsigned int m_Id;
		unsigned int m_VertexShaderId;
		unsigned int m_FragmentShaderId;
	};
}