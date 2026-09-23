#pragma once

struct ma_engine;

namespace Engine {
	class AudioSystem {
	public:
		static void Init();
		static void Shutdown();

		static ma_engine* GetEngine() { return s_Engine; }
	private:
		static ma_engine* s_Engine;
	};
}