#include "AudioSource.h"
#include "AudioSystem.h"
#include <miniaudio.h>
#include <iostream>

namespace Engine {
	AudioSource::AudioSource(std::shared_ptr<AudioClip> clip)
		: m_Clip(std::move(clip)) {
		if (!m_Clip || !m_Clip->IsValid() || !AudioSystem::GetEngine())
			return;

		m_Sound = new ma_sound();
		ma_result result = ma_sound_init_from_file(
			AudioSystem::GetEngine(),
			m_Clip->GetPath().c_str(),
			MA_SOUND_FLAG_DECODE,
			nullptr,
			nullptr,
			m_Sound
		);

		if (result != MA_SUCCESS) {
			std::cerr << "Failed to create audio source for: " << m_Clip->GetPath() << std::endl;
			delete m_Sound;
			m_Sound = nullptr;
			return;
		}

		m_Initialized = true;
	}

	AudioSource::~AudioSource() {
		Release();
	}

	AudioSource::AudioSource(AudioSource&& other) noexcept
		: m_Clip(std::move(other.m_Clip)), m_Sound(other.m_Sound), m_Initialized(other.m_Initialized) {
		other.m_Sound = nullptr;
		other.m_Initialized = false;
	}

	AudioSource& AudioSource::operator=(AudioSource&& other) noexcept {
		if (this != &other) {
			Release();
			m_Clip = std::move(other.m_Clip);
			m_Sound = other.m_Sound;
			m_Initialized = other.m_Initialized;
			other.m_Sound = nullptr;
			other.m_Initialized = false;
		}
		return *this;
	}

	void AudioSource::Release() {
		if (m_Initialized) {
			ma_sound_uninit(m_Sound);
		}
		delete m_Sound;
		m_Sound = nullptr;
		m_Initialized = false;
	}

	void AudioSource::Play() {
		if (m_Initialized) ma_sound_start(m_Sound);
	}

	void AudioSource::Pause() {
		if (m_Initialized) ma_sound_stop(m_Sound);
	}

	void AudioSource::Resume() {
		if (m_Initialized) ma_sound_start(m_Sound);
	}

	void AudioSource::Stop() {
		if (m_Initialized) {
			ma_sound_stop(m_Sound);
			ma_sound_seek_to_pcm_frame(m_Sound, 0);
		}
	}

	void AudioSource::SetVolume(float volume) {
		if (m_Initialized) ma_sound_set_volume(m_Sound, volume);
	}

	void AudioSource::SetLooping(bool looping) {
		if (m_Initialized) ma_sound_set_looping(m_Sound, looping ? MA_TRUE : MA_FALSE);
	}

	bool AudioSource::IsPlaying() const {
		return m_Initialized && ma_sound_is_playing(m_Sound);
	}
}