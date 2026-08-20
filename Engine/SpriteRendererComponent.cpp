#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Actor.h"
#include "TransformComponent.h"
#include "Renderer.h"


SpriteRendererComponent::SpriteRendererComponent(Actor* owner, std::shared_ptr<nu::Texture> texture, nu::Renderer* renderer)
    : Component(owner), m_texture(texture), m_renderer(renderer) {
}

void SpriteRendererComponent::Draw() {
    if (m_texture && m_renderer && owner) {
        if (auto* transform = owner->GetComponent<TransformComponent>()) {
            m_renderer->DrawTexture(m_texture.get(), transform->x, transform->y);
        }
    }
}

std::unique_ptr<Component> SpriteRendererComponent::Clone(Actor* newOwner) const {
    return std::make_unique<SpriteRendererComponent>(*this);
}