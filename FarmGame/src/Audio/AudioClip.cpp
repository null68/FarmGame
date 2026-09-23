#include "AudioClip.h"
#include <fstream>
#include <iostream>

namespace Engine {
	AudioClip::AudioClip(const std::string& path)
		: m_Path(path) {
		std::ifstream file(path, std::ios::binary);
		m_Valid = file.good();

		if (!m_Valid) {
			std::cerr << "Failed to open audio file: " << path << std::endl;
		}
	}
}