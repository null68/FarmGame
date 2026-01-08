#pragma once

#include "../Mesh/Mesh.h"
#include "../Shader/ShaderProgram.h"

namespace Engine {
	class Batch {
	public:
		Batch(ShaderProgram* shader);
		~Batch();
		void Begin();
		// moras i Material i transform
		void Submit(const Mesh& mesh);
		void End();
		void Flush();

		bool IsFull() const;

		inline ShaderProgram* GetShader() const { return m_Shader; }
	private:
		ShaderProgram* m_Shader;
	};
}