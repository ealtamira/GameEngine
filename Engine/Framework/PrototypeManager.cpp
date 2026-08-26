#include "pch.h"
#include "../Serialization/Json.h"
#include "PrototypeManager.h"
#include <rapidjson/document.h>
#include <iostream>

bool LoadScene(const std::string& filename, std::vector<std::unique_ptr<Actor>>& sceneActors)
{
    rapidjson::Document doc;
    if (!nu::json::Load(filename, doc))
    {
        return false;
    }

    if (doc.HasMember("prototypes") && doc["prototypes"].IsArray())
    {
        for (auto& protoVal : doc["prototypes"].GetArray())
        {
            std::string name;
            if (nu::json::Read(protoVal, "name", name))
            {
                auto actor = std::make_unique<Actor>();
                actor->Read(protoVal);
                PrototypeManager::Get().RegisterPrototype(name, std::move(actor));
            }
        }
    }

    if (doc.HasMember("actors") && doc["actors"].IsArray())
    {
        for (auto& actorVal : doc["actors"].GetArray())
        {
            auto actor = std::make_unique<Actor>();
            actor->Read(actorVal);
            sceneActors.push_back(std::move(actor));
        }
    }

    return true;
}