#include "pch.h"
#include "CircleColliderComponent.h"
#include <cmath>

CircleColliderComponent::CircleColliderComponent(Actor* owner)
    : Component(owner), radius(0.0f), offsetX(0.0f), offsetY(0.0f) {
}

CircleColliderComponent::CircleColliderComponent(Actor* owner, float r)
    : Component(owner), radius(r), offsetX(0.0f), offsetY(0.0f) {
}

CircleColliderComponent::CircleColliderComponent(Actor* owner, float r, float ox, float oy)
    : Component(owner), radius(r), offsetX(ox), offsetY(oy) {
}

bool CircleColliderComponent::CheckCollision(const CircleColliderComponent* other) const {
    return false;
}

void CircleColliderComponent::Read(const rapidjson::Value& value) {
    if (value.HasMember("radius") && value["radius"].IsNumber()) {
        radius = value["radius"].GetFloat();
    }
    if (value.HasMember("offsetX") && value["offsetX"].IsNumber()) {
        offsetX = value["offsetX"].GetFloat();
    }
    if (value.HasMember("offsetY") && value["offsetY"].IsNumber()) {
        offsetY = value["offsetY"].GetFloat();
    }
}

std::unique_ptr<Component> CircleColliderComponent::Clone(Actor* newOwner) const {
    return std::make_unique<CircleColliderComponent>(*this);
}