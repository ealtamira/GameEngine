#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(Actor* owner, float startX, float startY, float w, float h)
    : Component(owner), x(startX), y(startY), width(w), height(h) {
}

std::unique_ptr<Component> TransformComponent::Clone(Actor* newOwner) const {
    return std::make_unique<TransformComponent>(*this);
}