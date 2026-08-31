#pragma once
#include "../Engine/Resources/Resource.h"
#include <string>
#include <vector>
#include <memory>

namespace nu
{
    class Renderer;
    class Texture;

    struct LayerData {
        std::string name;
        int width;
        int height;
        std::vector<int> tiles;
    };

    struct TilemapData {
        int mapWidth = 0;
        int mapHeight = 0;
        int tileWidth = 0;
        int tileHeight = 0;
        std::vector<LayerData> layers;
        std::string tilesetImagePath;
    };

    class Tilemap : public Resource
    {
    public:
        Tilemap() = default;
        ~Tilemap() = default;

        bool Load(const std::string& filepath, Renderer& renderer);

        const TilemapData& GetData() const { return m_data; }
        std::shared_ptr<Texture> GetTexture() const { return m_tilesetTexture; }

    private:
        TilemapData m_data;
        std::shared_ptr<Texture> m_tilesetTexture;
    };
}