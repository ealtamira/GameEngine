#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Actor.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Engine.h"



SpriteRendererComponent::SpriteRendererComponent(Actor* owner)
    : Component(owner), m_texture(nullptr) {
    m_renderer = &nu::Engine::Get().GetRenderer();
}

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

void SpriteRendererComponent::Read(const rapidjson::Value& value) {
    if (value.HasMember("texture") && value["texture"].IsString()) {
        std::string textureName = value["texture"].GetString();

        m_texture = nu::Resources().Get<nu::Texture>(textureName, *m_renderer);
    }
}

std::unique_ptr<Component> SpriteRendererComponent::Clone(Actor* newOwner) const {
    return std::make_unique<SpriteRendererComponent>(newOwner, m_texture, m_renderer);
}