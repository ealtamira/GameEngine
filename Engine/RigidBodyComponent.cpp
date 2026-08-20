#include "pch.h"
#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent(Actor* owner, float vx, float vy)
    : Component(owner), velocityX(vx), velocityY(vy), accelerationX(0.0f), accelerationY(0.0f) {
}

void RigidBodyComponent::Update(float deltaTime) {
    velocityX += accelerationX * deltaTime;
    velocityY += accelerationY * deltaTime;
}

std::unique_ptr<Component> RigidBodyComponent::Clone(Actor* newOwner) const {
    return std::make_unique<RigidBodyComponent>(*this);
}
