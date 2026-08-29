#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "TextureFrames.h"
#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/TransformComponent.h"

namespace nu
{
    SpriteAnimationRendererComponent::SpriteAnimationRendererComponent(Actor* owner)
        : SpriteRendererComponent(owner), m_actor(owner) {
    }

    void SpriteAnimationRendererComponent::Update(float dt) {
        if (!m_isPlaying || !m_textureFrames || m_textureFrames->GetFrameCount() == 0) return;

        m_elapsedTime += dt;
        if (m_elapsedTime >= m_frameDuration) {
            m_elapsedTime = 0.0f;
            m_currentFrame++;

            if (m_currentFrame >= static_cast<int>(m_textureFrames->GetFrameCount())) {
                if (m_isLooping) {
                    m_currentFrame = 0;
                }
                else {
                    m_currentFrame = static_cast<int>(m_textureFrames->GetFrameCount()) - 1;
                    m_isPlaying = false;
                }
            }
        }
    }

    void SpriteAnimationRendererComponent::Draw() {
        if (!m_textureFrames || !m_textureFrames->GetTexture()) return;
        if (!m_actor) return;
        if (!m_renderer) return;

        auto* transform = m_actor->GetComponent<TransformComponent>();
        if (!transform) return;

        Texture* texture = m_textureFrames->GetTexture();
        SDL_Rect srcRect = m_textureFrames->GetFrame(m_currentFrame);

        SDL_FRect srcFRect = {
            static_cast<float>(srcRect.x),
            static_cast<float>(srcRect.y),
            static_cast<float>(srcRect.w),
            static_cast<float>(srcRect.h)
        };

        float scaledWidth = srcRect.w * m_actor->scale;
        float scaledHeight = srcRect.h * m_actor->scale;

        SDL_FRect destRect = {
            transform->x,
            transform->y,
            scaledWidth,
            scaledHeight
        };

        SDL_RenderTexture(m_renderer->GetRenderer(), texture->GetTexture(), &srcFRect, &destRect);
    }

    void SpriteAnimationRendererComponent::Read(const rapidjson::Value& value) {
        SpriteRendererComponent::Read(value);
    }

    std::unique_ptr<Component> SpriteAnimationRendererComponent::Clone(Actor* newOwner) const {
        std::unique_ptr<SpriteAnimationRendererComponent> clone = std::make_unique<SpriteAnimationRendererComponent>(newOwner);
        clone->m_textureFrames = m_textureFrames;
        clone->m_frameDuration = m_frameDuration;
        clone->m_isLooping = m_isLooping;
        clone->m_renderer = m_renderer;
        return clone;
    }

    void SpriteAnimationRendererComponent::SetTextureFrames(std::shared_ptr<TextureFrames> textureFrames, float frameDuration) {
        m_textureFrames = textureFrames;
        m_frameDuration = frameDuration;
        m_currentFrame = 0;
        m_elapsedTime = 0.0f;

        if (m_textureFrames && m_textureFrames->GetTexture()) {
            m_texture = std::shared_ptr<Texture>(m_textureFrames->GetTexture(), [](Texture*) {});
        }
    }
}