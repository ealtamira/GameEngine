#pragma once
#include "Audio.h"

namespace nu
{
	class Engine
	{
	public:
		static Engine& Get()
		{
			static Engine instance;
			return instance;
		}

		bool Initialize();
		void Update(float dt);
		void Shutdown();

		Audio& GetAudio() { return m_audio; }

	private:
		Engine() = default;
		~Engine() = default;
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		Audio m_audio;
	};
}