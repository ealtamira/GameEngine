#pragma once
#include "Framework/Actor.h"
#include "Framework/SpriteRendererComponent.h"
#include "TextureFrames.h"
#include <memory>

namespace nu
{
    class SpriteAnimationRendererComponent : public SpriteRendererComponent {
    public:
        SpriteAnimationRendererComponent(Actor* owner);

        void Update(float dt) override;
        void Draw() override;
        void Read(const rapidjson::Value& value) override;

        std::unique_ptr<Component> Clone(Actor* newOwner) const override;

        void SetTextureFrames(std::shared_ptr<TextureFrames> textureFrames, float frameDuration = 0.1f);
        void SetRenderer(class Renderer* renderer) { m_renderer = renderer; } 
    private:
        Actor* m_actor{ nullptr };
        class Renderer* m_renderer{ nullptr };
        std::shared_ptr<Texture> m_texture;
        std::shared_ptr<TextureFrames> m_textureFrames;
        int m_currentFrame = 0;
        float m_frameDuration = 0.1f;
        float m_elapsedTime = 0.0f;
        bool m_isLooping = true;
        bool m_isPlaying = true;
    };
}