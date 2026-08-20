#pragma once
#include "Audio.h"
#include "framework.h"
#include "Renderer.h"
#include "Input.h"
#include "Vector2.h"
#include "Mesh.h"
#include "Model.h"
#include "File.h"
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <vector>
#include <fmod.hpp>
#include "ParticleSystem.h"
#include "Font.h"
#include "Text.h"
#include <string>
#include <ctime>
#include <memory>
#include "Texture.h"
#include "ResourceManager.h"
#include "Json.h"
#include "Factory.h"
#include "Object.h"
#include "Creator.h"
#include "Actor.h"
#include "SpriteRendererComponent.h"
#include "RigidBodyComponent.h"
#include "CircleColliderComponent.h"

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