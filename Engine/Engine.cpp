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

        return true;


    }

    void Engine::Update(float dt)
    {
        m_audio.Update();
    }

    void Engine::Shutdown()
    {
        m_audio.Shutdown();
    }
}