#pragma once

#include <memory>
#include <string>

#include "../Component.h"
#include "../../Audio/AudioSource.h"
#include "../../Audio/AudioStorage.h"

namespace Engine {
	class AudioSourceComponent : public Component {
	public:
		explicit AudioSourceComponent(const std::string& clipName)
			: m_Source(AudioStorage::GetInstance().Get(clipName)) {
		}
		explicit AudioSourceComponent(std::shared_ptr<AudioClip> clip)
			: m_Source(std::move(clip)) {
		}

		void Play() { m_Source.Play(); }
		void Pause() { m_Source.Pause(); }
		void Resume() { m_Source.Resume(); }
		void Stop() { m_Source.Stop(); }
		void SetVolume(float volume) { m_Source.SetVolume(volume); }
		void SetLooping(bool looping) { m_Source.SetLooping(looping); }
		bool IsPlaying() const { return m_Source.IsPlaying(); }
	private:
		AudioSource m_Source;
	};
}