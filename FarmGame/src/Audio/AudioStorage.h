#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "AudioClip.h"

namespace Engine {
	class AudioStorage {
	public:
		static AudioStorage& GetInstance();

		std::shared_ptr<AudioClip> Load(const std::string& name, const std::string& filePath);
		std::shared_ptr<AudioClip> Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<AudioClip>> m_Clips;
	};
}
