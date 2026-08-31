#include "pch.h"
#include "Tilemap.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Resources/ResourceManager.h"
#include <fstream>
#include <filesystem>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace nu
{
    bool Tilemap::Load(const std::string& filepath, Renderer& renderer)
    {
        namespace fs = std::filesystem;

        fs::path mapPath(filepath);
        std::ifstream stream(mapPath);
        if (!stream.is_open())
        {
            mapPath = fs::path("Build") / filepath;
            stream.open(mapPath);
        }

        if (!stream.is_open()) return false;

        rapidjson::IStreamWrapper isw(stream);
        rapidjson::Document doc;
        doc.ParseStream(isw);

        if (doc.HasParseError() || !doc.IsObject()) return false;

        if (!doc.HasMember("width") || !doc.HasMember("height") || !doc.HasMember("tilewidth") || !doc.HasMember("tileheight") || !doc.HasMember("layers"))
        {
            return false;
        }

        m_data.layers.clear();

        m_data.mapWidth = doc["width"].GetInt();
        m_data.mapHeight = doc["height"].GetInt();
        m_data.tileWidth = doc["tilewidth"].GetInt();
        m_data.tileHeight = doc["tileheight"].GetInt();

        const auto& layers = doc["layers"];
        for (auto& layerObj : layers.GetArray())
        {
            LayerData ld;
            ld.name = layerObj["name"].GetString();
            ld.width = layerObj["width"].GetInt();
            ld.height = layerObj["height"].GetInt();

            const auto& dataArray = layerObj["data"];
            for (auto& tileVal : dataArray.GetArray())
            {
                ld.tiles.push_back(tileVal.GetInt());
            }

            m_data.layers.push_back(ld);
        }

        std::string tilesetImagePath = "Img/tile0.png";
        if (doc.HasMember("tilesets") && doc["tilesets"].IsArray() && !doc["tilesets"].GetArray().Empty())
        {
            const auto& firstTileset = doc["tilesets"][0];
            if (firstTileset.HasMember("image") && firstTileset["image"].IsString())
            {
                tilesetImagePath = firstTileset["image"].GetString();
            }
        }

        m_data.tilesetImagePath = tilesetImagePath;

        fs::path resolvedTilesetPath = mapPath.parent_path() / tilesetImagePath;
        if (!fs::exists(resolvedTilesetPath))
        {
            resolvedTilesetPath = fs::path(tilesetImagePath);
        }

        m_tilesetTexture = Resources().Get<Texture>(resolvedTilesetPath.string(), renderer);
        if (!m_tilesetTexture)
        {
            return false;
        }

        return true;
    }
}