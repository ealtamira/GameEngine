#pragma once
#include "Component.h"
#include <memory>

namespace nu {
    class Texture;
    class Renderer;
}

class SpriteRendererComponent : public Component {
public:
    SpriteRendererComponent(Actor* owner, std::shared_ptr<nu::Texture> texture, nu::Renderer* renderer);

    void Update(float dt) override {}
    void Draw() override;

    std::unique_ptr<Component> Clone(Actor* newOwner) const override;

private:
    std::shared_ptr<nu::Texture> m_texture;
    nu::Renderer* m_renderer;
};