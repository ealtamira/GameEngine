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

        Factory::Instance().Register("Player", std::make_unique<Creator<Player>>());
        Factory::Instance().Register("Enemy", std::make_unique<Creator<Enemy>>());
        Factory::Instance().Register("Projectile", std::make_unique<Creator<Projectile>>());

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