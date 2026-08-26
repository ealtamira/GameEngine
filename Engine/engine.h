#pragma once

#include "Audio/Audio.h"
#include "Renderer/Renderer.h"
#include "Physics/Physics.h"

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
        Renderer& GetRenderer() { return m_renderer; }
        Physics& GetPhysics() { return m_physics; }

    private:
        Engine() = default;
        ~Engine() = default;
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        Audio m_audio;
        Renderer m_renderer;
        Physics m_physics;
    };
}