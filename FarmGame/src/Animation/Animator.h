#pragma once

#include <memory>
#include "AnimationClip.h"

namespace Engine {
	class Animator {
	public:
		void Play(std::shared_ptr<AnimationClip> clip);
		void Pause();
		void Resume();
		void Stop();

		void Update(float deltaTime);

		void SetSpeed(float speed) { m_Speed = speed; }
		float GetSpeed() const { return m_Speed; }

		void SetLooping(bool looping) { m_Looping = looping; }
		bool IsLooping() const { return m_Looping; }

		bool IsPlaying() const { return m_Playing; }
		float GetCurrentTime() const { return m_CurrentTime; }

		const std::shared_ptr<AnimationClip>& GetCurrentClip() const { return m_CurrentClip; }
	private:
		std::shared_ptr<AnimationClip> m_CurrentClip;
		float m_CurrentTime = 0.0f;
		float m_Speed = 1.0f;
		bool m_Looping = false;
		bool m_Playing = false;
	};
}