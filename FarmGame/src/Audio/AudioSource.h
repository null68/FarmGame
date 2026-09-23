#pragma once

#include <memory>
#include "AudioClip.h"

struct ma_sound;

namespace Engine {
	class AudioSource {
	public:
		AudioSource() = default;
		explicit AudioSource(std::shared_ptr<AudioClip> clip);
		~AudioSource();

		AudioSource(const AudioSource&) = delete;
		AudioSource& operator=(const AudioSource&) = delete;
		AudioSource(AudioSource&& other) noexcept;
		AudioSource& operator=(AudioSource&& other) noexcept;

		void Play();
		void Pause();
		void Resume();
		void Stop();

		void SetVolume(float volume);
		void SetLooping(bool looping);

		bool IsPlaying() const;
		bool IsValid() const { return m_Initialized; }
	private:
		void Release();

		std::shared_ptr<AudioClip> m_Clip;
		ma_sound* m_Sound = nullptr;
		bool m_Initialized = false;
	};
}