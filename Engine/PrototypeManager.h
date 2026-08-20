#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Actor.h"

class PrototypeManager
{
public:
    static PrototypeManager& Get()
    {
        static PrototypeManager instance;
        return instance;
    }

    void RegisterPrototype(const std::string& name, std::unique_ptr<Actor> actor)
    {
        m_prototypes[name] = std::move(actor);
    }

    std::unique_ptr<Actor> Create(const std::string& name)
    {
        auto it = m_prototypes.find(name);
        if (it != m_prototypes.end())
        {
            return std::make_unique<Actor>(*it->second);
        }
        return nullptr;
    }

    void Clear()
    {
        m_prototypes.clear();
    }

private:
    PrototypeManager() = default;
    std::unordered_map<std::string, std::unique_ptr<Actor>> m_prototypes;
};