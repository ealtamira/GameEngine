#include "pch.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "Actor.h"

RigidBodyComponent::RigidBodyComponent(Actor* owner)
    : Component(owner), velocityX(0.0f), velocityY(0.0f), accelerationX(0.0f), accelerationY(0.0f) {
}

RigidBodyComponent::RigidBodyComponent(Actor* owner, float vx, float vy)
    : Component(owner), velocityX(vx), velocityY(vy), accelerationX(0.0f), accelerationY(0.0f) {
}

void RigidBodyComponent::Update(float deltaTime) {
    if (owner) {
        velocityX += accelerationX * deltaTime;
        velocityY += accelerationY * deltaTime;

        if (auto* transform = owner->GetComponent<TransformComponent>()) {
            transform->x += velocityX * deltaTime;
            transform->y += velocityY * deltaTime;
        }
    }
}

void RigidBodyComponent::Read(const rapidjson::Value& value) {
    if (value.HasMember("velocityX") && value["velocityX"].IsNumber()) {
        velocityX = value["velocityX"].GetFloat();
    }
    if (value.HasMember("velocityY") && value["velocityY"].IsNumber()) {
        velocityY = value["velocityY"].GetFloat();
    }
    if (value.HasMember("accelerationX") && value["accelerationX"].IsNumber()) {
        accelerationX = value["accelerationX"].GetFloat();
    }
    if (value.HasMember("accelerationY") && value["accelerationY"].IsNumber()) {
        accelerationY = value["accelerationY"].GetFloat();
    }
}

std::unique_ptr<Component> RigidBodyComponent::Clone(Actor* newOwner) const {
    return std::make_unique<RigidBodyComponent>(*this);
}
