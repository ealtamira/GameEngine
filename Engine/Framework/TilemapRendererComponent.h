#pragma once

#include "Component.h"
#include <memory>

class Actor;

namespace nu
{
    class Tilemap;
    class Renderer;

    class TilemapRendererComponent : public Component
    {
    public:
        TilemapRendererComponent(Actor* owner, std::shared_ptr<Tilemap> tilemap = nullptr, int layerIndex = 0, Renderer* renderer = nullptr);
        ~TilemapRendererComponent() override = default;

        void Update(float dt) override;
        void Draw() override;

        std::unique_ptr<Component> Clone(Actor* newOwner) const override;
        void Read(const rapidjson::Value& value) override;

        void SetTilemap(std::shared_ptr<Tilemap> tilemap);
        void SetLayerIndex(int index) { m_layerIndex = index; }
        void SetRenderer(Renderer* renderer) { m_renderer = renderer; }

    private:
        void CreateCollisions();

        std::shared_ptr<Tilemap> m_tilemap;
        Renderer* m_renderer = nullptr;
        int m_layerIndex = 0;
        int m_collisionLayerIndex = -1;
    };
}