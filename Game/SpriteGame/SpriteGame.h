#pragma once
#pragma once

#include "../../Engine/pch.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Resources/ResourceManager.h"
#include "../../Engine/Renderer/Font.h"
#include "../../Engine/Renderer/Text.h"
#include "../../Engine/Renderer/Texture.h"

class SpriteGame
{
public:
    bool Initialize();
    void Update(float dt);
    void Draw(nu::Renderer& renderer);
    void Shutdown();

private:
    struct Entity
    {
        float x, y;
        float width, height;
        float speed;
        bool active;

        bool Intersects(const Entity& other) const
        {
            return (x < other.x + other.width &&
                x + width > other.x &&
                y < other.y + other.height &&
                y + height > other.y);
        }
    };

    enum class GameState
    {
        TitleScreen,
        InGame,
        GameOver
    };

    GameState m_currentState = GameState::TitleScreen;
    Entity m_player = { 512.0f, 360.0f, 40.0f, 40.0f, 300.0f, true };
    int m_score = 0;
    int m_health = 100;

    std::vector<Entity> m_enemies;
    std::vector<Entity> m_bullets;
    std::vector<Entity> m_pickups;

    float m_enemySpawnTimer = 0.0f;
    float m_shootCooldown = 0.0f;

    std::shared_ptr<nu::Font> m_font;
    std::unique_ptr<nu::Text> m_uiText;

    std::shared_ptr<nu::Texture> m_backgroundTexture;
    std::shared_ptr<nu::Texture> m_playerTexture;
    std::shared_ptr<nu::Texture> m_enemyTexture;
    std::shared_ptr<nu::Texture> m_bulletTexture;
    std::shared_ptr<nu::Texture> m_pickupTexture;
};