#pragma once

namespace Engine {
	class VertexBuffer {
	private:
		unsigned int m_Id;
	public:
		VertexBuffer(const void* data, unsigned int size);
		void Bind() const;
		void Unbind() const;
		void Delete() const;
	};
}