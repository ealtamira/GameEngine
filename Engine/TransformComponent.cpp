#include "pch.h"
#include "TransformComponent.h"
#include "Json.h"

TransformComponent::TransformComponent(Actor* owner, float startX, float startY, float w, float h)
    : Component(owner), x(startX), y(startY), width(w), height(h) {
}

void TransformComponent::Read(const rapidjson::Value& value) {
    Component::Read(value);
    nu::json::Read(value, "x", x);
    nu::json::Read(value, "y", y);
    nu::json::Read(value, "width", width);
    nu::json::Read(value, "height", height);
}

std::unique_ptr<Component> TransformComponent::Clone(Actor* newOwner) const {
    return std::make_unique<TransformComponent>(newOwner, x, y, width, height);
}