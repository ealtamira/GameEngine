#include "pch.h"
#include "CircleColliderComponent.h"
#include <cmath>

CircleColliderComponent::CircleColliderComponent(Actor* owner, float radius, float offsetX, float offsetY)
    : Component(owner), radius(radius), offsetX(offsetX), offsetY(offsetY) {
}

bool CircleColliderComponent::CheckCollision(const CircleColliderComponent* other) const {
    return false;
}

std::unique_ptr<Component> CircleColliderComponent::Clone(Actor* newOwner) const {
    return std::make_unique<CircleColliderComponent>(*this);
}