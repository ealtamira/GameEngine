#include "SpriteGame.h"
#include <cstdlib>
#include <ctime>

bool SpriteGame::Initialize()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    TTF_Init();

    m_font = nu::Resources().GetWithID<nu::Font>("ui_font", "fonts/Western.ttf", 24.0f);
    m_uiText = std::make_unique<nu::Text>(m_font);

    m_backgroundTexture = nu::Resources().Get<nu::Texture>("Img/darkPurple.png", nu::Engine::Get().GetRenderer());
    m_playerTexture = nu::Resources().Get<nu::Texture>("Img/player.png", nu::Engine::Get().GetRenderer());
    m_enemyTexture = nu::Resources().Get<nu::Texture>("Img/enemy.png", nu::Engine::Get().GetRenderer());
    m_bulletTexture = nu::Resources().Get<nu::Texture>("Img/bullet.png", nu::Engine::Get().GetRenderer());
    m_pickupTexture = nu::Resources().Get<nu::Texture>("Img/pickup.png", nu::Engine::Get().GetRenderer());

    nu::Engine::Get().GetAudio().AddSound("bgm", "audio/switch16.ogg");
    nu::Engine::Get().GetAudio().AddSound("shoot", "audio/shoot-h.ogg");
    nu::Engine::Get().GetAudio().AddSound("explosion", "audio/explosion-c.ogg");
    nu::Engine::Get().GetAudio().AddSound("pickup", "audio/coin-c.ogg");
    nu::Engine::Get().GetAudio().AddSound("player_hit", "audio/hurt-d.ogg");
    m_currentState = GameState::TitleScreen;
    m_player = { 512.0f, 360.0f, 40.0f, 40.0f, 300.0f, true };
    m_score = 0;
    m_health = 100;
    m_enemySpawnTimer = 0.0f;
    m_shootCooldown = 0.0f;

    return true;
}

void SpriteGame::Update(float dt)
{
    auto& input = nu::Engine::Get().GetInput();

    if (m_currentState == GameState::TitleScreen)
    {
        if (input.GetKeyPressed(SDL_SCANCODE_SPACE))
        {
            m_currentState = GameState::InGame;
            m_score = 0;
            m_health = 100;
            m_player.x = 512.0f;
            m_player.y = 360.0f;
            m_enemies.clear();
            m_bullets.clear();
            m_pickups.clear();

            nu::Engine::Get().GetAudio().PlaySound("bgm");
        }
    }
    else if (m_currentState == GameState::InGame)
    {
        if (input.GetKeyDown(SDL_SCANCODE_W)) m_player.y -= m_player.speed * dt;
        if (input.GetKeyDown(SDL_SCANCODE_S)) m_player.y += m_player.speed * dt;
        if (input.GetKeyDown(SDL_SCANCODE_A)) m_player.x -= m_player.speed * dt;
        if (input.GetKeyDown(SDL_SCANCODE_D)) m_player.x += m_player.speed * dt;

        if (m_player.x < 0) m_player.x = 0;
        if (m_player.x > 1024 - m_player.width) m_player.x = 1024 - m_player.width;
        if (m_player.y < 0) m_player.y = 0;
        if (m_player.y > 720 - m_player.height) m_player.y = 720 - m_player.height;

        if (m_shootCooldown > 0) m_shootCooldown -= dt;
        if (input.GetKeyPressed(SDL_SCANCODE_SPACE) && m_shootCooldown <= 0.0f)
        {
            m_bullets.push_back({ m_player.x + 15.0f, m_player.y - 10.0f, 10.0f, 20.0f, 500.0f, true });
            nu::Engine::Get().GetAudio().PlaySound("shoot");
            m_shootCooldown = 0.25f;
        }

        for (auto& bullet : m_bullets)
        {
            if (bullet.active)
            {
                bullet.y -= bullet.speed * dt;
                if (bullet.y < 0) bullet.active = false;
            }
        }

        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0.0f)
        {
            float randomX = static_cast<float>(std::rand() % 980);
            m_enemies.push_back({ randomX, -50.0f, 40.0f, 40.0f, 150.0f, true });
            m_enemySpawnTimer = 1.0f;
        }

        for (auto& enemy : m_enemies)
        {
            if (!enemy.active) continue;

            enemy.y += enemy.speed * dt;

            for (auto& bullet : m_bullets)
            {
                if (bullet.active && enemy.Intersects(bullet))
                {
                    enemy.active = false;
                    bullet.active = false;
                    m_score += 100;
                    nu::Engine::Get().GetAudio().PlaySound("explosion");

                    if (std::rand() % 100 < 15)
                    {
                        m_pickups.push_back({ enemy.x, enemy.y, 25.0f, 25.0f, 50.0f, true });
                    }
                }
            }

            if (enemy.Intersects(m_player))
            {
                enemy.active = false;
                m_health -= 20;
                nu::Engine::Get().GetAudio().PlaySound("player_hit");
                if (m_health <= 0)
                {
                    m_currentState = GameState::GameOver;
                }
            }

            if (enemy.y > 720) enemy.active = false;
        }

        for (auto& pickup : m_pickups)
        {
            if (!pickup.active) continue;
            pickup.y += pickup.speed * dt;

            if (pickup.Intersects(m_player))
            {
                pickup.active = false;
                m_health += 20;
                if (m_health > 100) m_health = 100;
                nu::Engine::Get().GetAudio().PlaySound("pickup");
            }
        }
    }
    else if (m_currentState == GameState::GameOver)
    {
        if (input.GetKeyPressed(SDL_SCANCODE_R))
        {
            m_currentState = GameState::TitleScreen;
        }
    }

}

void SpriteGame::Draw(nu::Renderer& renderer)
{
    renderer.SetColor(0, 0, 0);
    renderer.Clear();

    if (m_backgroundTexture)
    {
        SDL_FRect bgRect = { 0.0f, 0.0f, 1024.0f, 720.0f };
        SDL_RenderTexture(renderer.GetRenderer(), m_backgroundTexture->GetTexture(), nullptr, &bgRect);
    }

    if (m_currentState == GameState::TitleScreen)
    {
        m_uiText->Create(renderer, "ARENA SHOOTER - PRESS SPACE TO START", { 1.0f, 1.0f, 1.0f, 1.0f });
        m_uiText->Draw(renderer, 250, 300);
    }
    else if (m_currentState == GameState::InGame)
    {
        if (m_playerTexture) renderer.DrawTexture(m_playerTexture.get(), m_player.x, m_player.y);

        for (const auto& bullet : m_bullets)
        {
            if (bullet.active && m_bulletTexture)
            {
                renderer.DrawTexture(m_bulletTexture.get(), bullet.x, bullet.y);
            }
        }

        for (const auto& enemy : m_enemies)
        {
            if (enemy.active && m_enemyTexture)
            {
                renderer.DrawTexture(m_enemyTexture.get(), enemy.x, enemy.y);
            }
        }

        for (const auto& pickup : m_pickups)
        {
            if (pickup.active && m_pickupTexture)
            {
                renderer.DrawTexture(m_pickupTexture.get(), pickup.x, pickup.y);
            }
        }

        m_uiText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f, 1.0f });
        m_uiText->Draw(renderer, 20, 20);

        m_uiText->Create(renderer, "Health: " + std::to_string(m_health), { 0.2f, 1.0f, 0.2f, 1.0f });
        m_uiText->Draw(renderer, 20, 50);
    }
    else if (m_currentState == GameState::GameOver)
    {
        m_uiText->Create(renderer, "GAME OVER", { 1.0f, 0.0f, 0.0f, 1.0f });
        m_uiText->Draw(renderer, 400, 250);

        m_uiText->Create(renderer, "Final Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f, 1.0f });
        m_uiText->Draw(renderer, 380, 300);

        m_uiText->Create(renderer, "PRESS R TO RESTART", { 1.0f, 1.0f, 1.0f, 1.0f });
        m_uiText->Draw(renderer, 350, 350);
    }
}

void SpriteGame::Shutdown()
{
    TTF_Quit();
}