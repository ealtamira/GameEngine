#include "pch.h"
#include "ParticleSystem.h"
#include "Renderer.h" 

namespace nu
{
    bool ParticleSystem::Initialize(size_t size)
    {
        m_particles.resize(size);
        return true;
    }

    void ParticleSystem::Shutdown()
    {
        m_particles.clear();
    }

    void ParticleSystem::Update(float dt)
    {
        for (auto& particle : m_particles)
        {
            if (!particle.active) continue;

            particle.lifespan -= dt;
            particle.active = (particle.lifespan > 0);
            particle.position += particle.velocity * dt;
        }
    }

    void ParticleSystem::Draw(Renderer& renderer)
    {
        for (auto& particle : m_particles)
        {
            if (particle.active)
            {
                renderer.SetColor(
                    static_cast<uint8_t>(particle.color.r * 255),
                    static_cast<uint8_t>(particle.color.g * 255),
                    static_cast<uint8_t>(particle.color.b * 255),
                    255
                );

                renderer.DrawPoint(particle.position.x, particle.position.y);
                renderer.DrawPoint(particle.position.x + 1, particle.position.y);
                renderer.DrawPoint(particle.position.x - 1, particle.position.y);
                renderer.DrawPoint(particle.position.x, particle.position.y + 1);
                renderer.DrawPoint(particle.position.x, particle.position.y - 1);
            }
        }
    }

    void ParticleSystem::AddParticle(const Particle& particle)
    {
        Particle* freeParticle = GetFreeParticle();

        if (freeParticle)
        {
            *freeParticle = particle;
            freeParticle->active = true;
        }
    }

    Particle* ParticleSystem::GetFreeParticle()
    {
        for (auto& particle : m_particles)
        {
            if (!particle.active)
            {
                return &particle;
            }
        }
        return nullptr;
    }
}