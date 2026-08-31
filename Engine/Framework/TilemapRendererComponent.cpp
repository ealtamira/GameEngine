#include "pch.h"
#include "TilemapRendererComponent.h"
#include "Tilemap.h"
#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"
#include "RigidBodyComponent.h"
// #include "Physics/CircleColliderComponent.h"

namespace nu
{
    TilemapRendererComponent::TilemapRendererComponent(Actor* owner, std::shared_ptr<Tilemap> tilemap, int layerIndex, Renderer* renderer)
        : Component(owner), m_tilemap(tilemap), m_renderer(renderer), m_layerIndex(layerIndex)
    {
        if (m_tilemap) {
            CreateCollisions();
        }
    }

    void TilemapRendererComponent::SetTilemap(std::shared_ptr<Tilemap> tilemap)
    {
        m_tilemap = tilemap;
        CreateCollisions();
    }

    void TilemapRendererComponent::Update(float dt)
    {
    }

    void TilemapRendererComponent::Draw()
    {
        if (!m_tilemap || !owner) return;

        const auto& data = m_tilemap->GetData();
        if (m_layerIndex < 0 || m_layerIndex >= static_cast<int>(data.layers.size())) {
            return;
        }

        const auto& layer = data.layers[m_layerIndex];
        std::shared_ptr<Texture> texture = m_tilemap->GetTexture();
        if (!texture) return;

        float texW = 0.0f;
        float texH = 0.0f;
        SDL_GetTextureSize(texture->GetTexture(), &texW, &texH);
        int texWidth = static_cast<int>(texW);

        int tilesetCols = (data.tileWidth > 0) ? (texWidth / data.tileWidth) : 1;

        float actorX = owner->x;
        float actorY = owner->y;

        Renderer* renderer = m_renderer ? m_renderer : &Engine::Get().GetRenderer();
        if (!renderer) return;

        for (int y = 0; y < layer.height; ++y)
        {
            for (int x = 0; x < layer.width; ++x)
            {
                int tileIndex = y * layer.width + x;
                int gid = layer.tiles[tileIndex];

                if (gid == 0) continue;

                int localId = gid - 1;
                float srcX = static_cast<float>((localId % tilesetCols) * data.tileWidth);
                float srcY = static_cast<float>((localId / tilesetCols) * data.tileHeight);
                float srcW = static_cast<float>(data.tileWidth);
                float srcH = static_cast<float>(data.tileHeight);

                float destX = actorX + static_cast<float>(x * data.tileWidth);
                float destY = actorY + static_cast<float>(y * data.tileHeight);
                float destW = static_cast<float>(data.tileWidth);
                float destH = static_cast<float>(data.tileHeight);

                renderer->DrawSprite(texture.get(), srcX, srcY, srcW, srcH, destX, destY, destW, destH);
            }
        }
    }

    void TilemapRendererComponent::CreateCollisions()
    {
        if (!m_tilemap || !owner) return;

        const auto& data = m_tilemap->GetData();

        int targetCollisionLayer = m_collisionLayerIndex;
        if (targetCollisionLayer < 0 || targetCollisionLayer >= static_cast<int>(data.layers.size()))
        {
            for (size_t i = 0; i < data.layers.size(); ++i)
            {
                if (data.layers[i].name == "collision" || data.layers[i].name == "Collision")
                {
                    targetCollisionLayer = static_cast<int>(i);
                    break;
                }
            }
            if (targetCollisionLayer < 0) targetCollisionLayer = m_layerIndex;
        }

        if (targetCollisionLayer < 0 || targetCollisionLayer >= static_cast<int>(data.layers.size())) return;

        const auto& layer = data.layers[targetCollisionLayer];

        for (int y = 0; y < layer.height; ++y)
        {
            for (int x = 0; x < layer.width; ++x)
            {
                int tileIndex = y * layer.width + x;
                int gid = layer.tiles[tileIndex];

                if (gid == 0) continue;
            }
        }
    }

    std::unique_ptr<Component> TilemapRendererComponent::Clone(Actor* newOwner) const
    {
        return std::make_unique<TilemapRendererComponent>(newOwner, m_tilemap, m_layerIndex, m_renderer);
    }

    void TilemapRendererComponent::Read(const rapidjson::Value& value)
    {
        std::string filename;
        if (value.HasMember("filename") && value["filename"].IsString()) {
            filename = value["filename"].GetString();
            m_tilemap = Resources().Get<Tilemap>(filename, Engine::Get().GetRenderer());
            CreateCollisions();
        }

        if (value.HasMember("layer") && value["layer"].IsInt()) {
            m_layerIndex = value["layer"].GetInt();
        }

        if (value.HasMember("collision_layer") && value["collision_layer"].IsInt()) {
            m_collisionLayerIndex = value["collision_layer"].GetInt();
            CreateCollisions();
        }
    }
}