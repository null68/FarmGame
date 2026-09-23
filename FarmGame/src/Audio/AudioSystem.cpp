#include "AudioSystem.h"
#include <miniaudio.h>
#include <iostream>

namespace Engine {
	ma_engine* AudioSystem::s_Engine = nullptr;

	void AudioSystem::Init() {
		if (s_Engine)
			return;

		s_Engine = new ma_engine();
		if (ma_engine_init(nullptr, s_Engine) != MA_SUCCESS) {
			std::cerr << "Failed to initialize audio engine." << std::endl;
			delete s_Engine;
			s_Engine = nullptr;
		}
	}

	void AudioSystem::Shutdown() {
		if (!s_Engine)
			return;

		ma_engine_uninit(s_Engine);
		delete s_Engine;
		s_Engine = nullptr;
	}
}