#pragma once

#include <string>

namespace Engine {
	class AudioClip {
	public:
		explicit AudioClip(const std::string& path);

		const std::string& GetPath() const { return m_Path; }
		bool IsValid() const { return m_Valid; }
	private:
		std::string m_Path;
		bool m_Valid = false;
	};
}