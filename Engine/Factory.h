#pragma once
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include "ICreator.h"
#include "Object.h"

class Factory {
private:
    std::map<std::string, std::unique_ptr<ICreator>> m_creators;

    Factory() = default;
    ~Factory() = default;
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

public:
    static Factory& Instance() {
        static Factory instance;
        return instance;
    }

    void Register(const std::string& name, std::unique_ptr<ICreator> creator) {
        if (m_creators.find(name) == m_creators.end()) {
            m_creators[name] = std::move(creator);
        }
        else {
            std::cerr << "Warning: Type '" << name << "' is already registered." << std::endl;
        }
    }

    Object* Create(const std::string& name) {
        auto it = m_creators.find(name);

        if (it != m_creators.end()) {
            return it->second->Create();
        }

        std::cerr << "Error: Actor type '" << name << "' not registered in Factory." << std::endl;
        return nullptr;
    }
};

struct RegisterHelper {
    RegisterHelper(const std::string& name, std::unique_ptr<ICreator> creator) {
        Factory::Instance().Register(name, std::move(creator));
    }
};