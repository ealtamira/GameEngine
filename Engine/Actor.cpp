#include "pch.h"
#include "Actor.h"
#include "Json.h"
#include "SpriteRendererComponent.h"
#include "RigidBodyComponent.h"
#include "CircleColliderComponent.h"

Actor::Actor() = default;

Actor::~Actor() = default;

Actor::Actor(const Actor& other) {
    name = other.name;
    tag = other.tag;
    x = other.x;
    y = other.y;
    scale = other.scale;
    rotation = other.rotation;
    for (const auto& comp : other.components) {
        components.push_back(comp->Clone(this));
    }
}

Actor& Actor::operator=(const Actor& other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    tag = other.tag;
    x = other.x;
    y = other.y;
    scale = other.scale;
    rotation = other.rotation;
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

void Actor::Read(const rapidjson::Value& value)
{
    nu::json::Read(value, "name", name);
    nu::json::Read(value, "tag", tag);
    nu::json::Read(value, "x", x);
    nu::json::Read(value, "y", y);
    nu::json::Read(value, "scale", scale);
    nu::json::Read(value, "rotation", rotation);

    if (value.HasMember("components") && value["components"].IsArray())
    {
        for (auto& compValue : value["components"].GetArray())
        {
            std::string type;
            if (nu::json::Read(compValue, "type", type))
            {
                Component* component = nullptr;

                if (type == "SpriteRenderer")
                {
                    component = AddComponent<SpriteRendererComponent>();
                }
                else if (type == "RigidBody")
                {
                    component = AddComponent<RigidBodyComponent>();
                }
                else if (type == "CircleCollider")
                {
                    component = AddComponent<CircleColliderComponent>();
                }

                if (component)
                {
                    component->Read(compValue);
                }
            }
        }
    }
}