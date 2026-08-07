#include "pch.h"
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
#include "Audio.h"
#include <string>
#include <ctime>
#include <memory>
#include "Texture.h"
#include "ResourceManager.h"



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

        bool Initialize()
        {
            if (!m_audio.Initialize())
            {
                std::cerr << "Failed to initialize Audio system!" << std::endl;
                return false;
            }
            return true;
        }

        void Update(float dt)
        {
            m_audio.Update();
        }

        void Shutdown()
        {
            m_audio.Shutdown();
        }

        Audio& GetAudio() { return m_audio; }

    private:
        Engine() = default;
        ~Engine() = default;
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        Audio m_audio;
    };
}