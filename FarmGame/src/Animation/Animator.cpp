#include "Animator.h"
#include <cmath>

namespace Engine {
	void Animator::Play(std::shared_ptr<AnimationClip> clip) {
		if (!clip)
			return;

		m_CurrentClip = std::move(clip);
		m_CurrentTime = 0.0f;
		m_Looping = m_CurrentClip->Loop;
		m_Playing = true;
	}

	void Animator::Pause() {
		m_Playing = false;
	}

	void Animator::Resume() {
		if (m_CurrentClip)
			m_Playing = true;
	}

	void Animator::Stop() {
		m_Playing = false;
		m_CurrentTime = 0.0f;
	}

	void Animator::Update(float deltaTime) {
		if (!m_Playing || !m_CurrentClip)
			return;

		m_CurrentTime += deltaTime * m_Speed;

		float length = m_CurrentClip->Length;
		if (length <= 0.0f)
			return;

		if (m_CurrentTime > length) {
			if (m_Looping) {
				m_CurrentTime = std::fmod(m_CurrentTime, length);
			}
			else {
				m_CurrentTime = length;
				m_Playing = false;
			}
		}
	}
}