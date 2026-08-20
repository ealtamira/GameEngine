#include "pch.h"
#include "Actor.h"

Actor::Actor() = default;

Actor::~Actor() = default;

Actor::Actor(const Actor& other) {
    for (const auto& comp : other.components) {
        components.push_back(comp->Clone(this));
    }
}

Actor& Actor::operator=(const Actor& other) {
    if (this == &other) {
        return *this;
    }

    components.clear();
    for (const auto& comp : other.components) {
        components.push_back(comp->Clone(this));
    }

    return *this;
}

void Actor::Update(float deltaTime) {
    for (auto& comp : components) {
        comp->Update(deltaTime);
    }
}

void Actor::Draw() {
    for (auto& comp : components) {
        comp->Draw();
    }
}