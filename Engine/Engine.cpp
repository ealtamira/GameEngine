#include "pch.h"
#include "Engine.h"
#include <iostream>

namespace nu
{
    bool Engine::Initialize()
    {
        if (!m_audio.Initialize())
        {
            std::cerr << "Failed to initialize Audio system!" << std::endl;
            return false;
        }

        if (!m_physics.Initialize())
        {
            std::cerr << "Failed to initialize Physics system!" << std::endl;
            return false;
        }

        return true;
    }

    void Engine::Update(float dt)
    {
        m_audio.Update();
        m_physics.Update(dt);
    }

    void Engine::Shutdown()
    {
        m_audio.Shutdown();
        m_physics.Shutdown();
    }
}