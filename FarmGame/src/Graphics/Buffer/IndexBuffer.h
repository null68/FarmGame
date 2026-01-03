#pragma once

namespace Engine {
	class IndexBuffer {
	private:
		unsigned int m_Id;
		unsigned int m_Count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		void Bind() const;
		void Unbind() const;
		void Delete() const;
	};
}