#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <utility>
#include "Component.h"

class Actor {
private:
    std::vector<std::unique_ptr<Component>> components;

public:
    Actor();
    virtual ~Actor();

    Actor(const Actor& other);
    Actor& operator=(const Actor& other);

    Actor(Actor&&) noexcept = default;
    Actor& operator=(Actor&&) noexcept = default;

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        auto newComponent = std::make_unique<T>(this, std::forward<Args>(args)...);
        T* rawPtr = newComponent.get();
        components.push_back(std::move(newComponent));
        return rawPtr;
    }

    template <typename T>
    T* GetComponent() {
        for (auto& comp : components) {
            if (T* casted = dynamic_cast<T*>(comp.get())) {
                return casted;
            }
        }
        return nullptr;
    }

    virtual void Update(float deltaTime);
    virtual void Draw();
};