#include "AudioStorage.h"
#include <stdexcept>

namespace Engine {
	AudioStorage& AudioStorage::GetInstance()
	{
		static AudioStorage instance;
		return instance;
	}

	std::shared_ptr<AudioClip> AudioStorage::Load(const std::string& name, const std::string& filePath) {
		if (Exists(name))
			return m_Clips[name];

		auto clip = std::make_shared<AudioClip>(filePath);
		m_Clips[name] = clip;
		return clip;
	}

	std::shared_ptr<AudioClip> AudioStorage::Get(const std::string& name)
	{
		if (Exists(name))
			return m_Clips[name];

		throw std::runtime_error("Audio clip with name " + name + " does not exist in storage.");
	}

	bool AudioStorage::Exists(const std::string& name) const {
		return m_Clips.find(name) != m_Clips.end();
	}
}