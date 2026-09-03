#pragma once

#include "../../Engine/pch.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Resources/ResourceManager.h"
#include "../../Engine/Renderer/Font.h"
#include "../../Engine/Renderer/Text.h"
#include "../../Engine/Renderer/Texture.h"
#include <vector>

class SpriteGame
{
public:
    bool Initialize();
    void Update(float dt);
    void Draw(nu::Renderer& renderer);
    void Shutdown();

private:
    struct Entity {
        float x, y;
        float width, height;
        float speed;
        int facingRight;
        bool active = true;
        bool isDead = false;
        float deathAnimTimer = 0.0f;
        int deathCurrentFrame = 0;
        int type = 0;

        bool Intersects(const Entity& other) const {
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
    Entity m_player = { 100.0f, 500.0f, 50.0f, 60.0f, 250.0f, true };
    int m_score = 0;
    int m_health = 100;

    std::vector<Entity> m_enemies;
    std::vector<std::shared_ptr<nu::Texture>> m_enemyDeadFrames;
    std::vector<std::shared_ptr<nu::Texture>> m_femaleEnemyDeadFrames;
    float m_enemySpawnTimer = 0.0f;
    float m_attackCooldown = 0.0f;
    bool m_isAttacking = false;
    float m_attackAnimTimer = 0.0f;


    std::vector<std::shared_ptr<nu::Texture>> m_enemyWalkFrames;
    std::vector<std::shared_ptr<nu::Texture>> m_femaleEnemyWalkFrames;
    float m_enemyAnimTimer = 0.0f;
    int m_enemyCurrentFrame = 0;

    std::vector<std::shared_ptr<nu::Texture>> m_playerWalkFrames;
    float m_playerAnimTimer = 0.0f;
    int m_playerCurrentFrame = 0;

    std::vector<std::shared_ptr<nu::Texture>> m_playerHurtFrames;
    bool m_isHurt = false;
    float m_hurtAnimTimer = 0.0f;
    int m_hurtCurrentFrame = 0;

    std::vector<std::shared_ptr<nu::Texture>> m_playerSlideFrames;
    float m_slideAnimTimer = 0.0f;
    int m_slideCurrentFrame = 0;

    std::shared_ptr<nu::Font> m_font;
    std::unique_ptr<nu::Text> m_uiText;

    std::shared_ptr<nu::Texture> m_backgroundTexture;
    std::shared_ptr<nu::Texture> m_playerTexture;
    std::shared_ptr<nu::Texture> m_enemyTexture;
    std::shared_ptr<nu::Texture> m_punchEffectTexture;
};