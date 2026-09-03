#include "SpriteGame.h"
#include <cstdlib>
#include <ctime>
#include <string>

bool SpriteGame::Initialize()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    TTF_Init();

    m_font = nu::Resources().GetWithID<nu::Font>("ui_font", "fonts/Western.ttf", 24.0f);
    m_uiText = std::make_unique<nu::Text>(m_font);

    m_backgroundTexture = nu::Resources().Get<nu::Texture>("Img/BG.png", nu::Engine::Get().GetRenderer());

    m_playerWalkFrames.clear();
    for (int i = 1; i <= 10; ++i)
    {
        std::string path = "Img/Cat/Walk (" + std::to_string(i) + ").png";
        auto tex = nu::Resources().Get<nu::Texture>(path, nu::Engine::Get().GetRenderer());
        m_playerWalkFrames.push_back(tex);
    }

    m_playerHurtFrames.clear();
    for (int i = 1; i <= 10; ++i)
    {
        std::string path = "Img/Cat/Hurt (" + std::to_string(i) + ").png";
        auto tex = nu::Resources().Get<nu::Texture>(path, nu::Engine::Get().GetRenderer());
        m_playerHurtFrames.push_back(tex);
    }

    m_playerSlideFrames.clear();
    for (int i = 1; i <= 10; ++i)
    {
        std::string path = "Img/Cat/Slide (" + std::to_string(i) + ").png";
        auto tex = nu::Resources().Get<nu::Texture>(path, nu::Engine::Get().GetRenderer());
        m_playerSlideFrames.push_back(tex);
    }

    m_enemyWalkFrames.clear();
    for (int i = 1; i <= 10; ++i)
    {
        std::string path = "Img/ZombieMale/Walk (" + std::to_string(i) + ").png";
        auto tex = nu::Resources().Get<nu::Texture>(path, nu::Engine::Get().GetRenderer());
        m_enemyWalkFrames.push_back(tex);
    }

    m_enemyDeadFrames.clear();
    for (int i = 1; i <= 12; ++i)
    {
        std::string path = "Img/ZombieMale/Dead (" + std::to_string(i) + ").png";
        auto tex = nu::Resources().Get<nu::Texture>(path, nu::Engine::Get().GetRenderer());
        m_enemyDeadFrames.push_back(tex);
    }

    m_femaleEnemyWalkFrames.clear();
    for (int i = 1; i <= 10; ++i)
    {
        std::string path = "Img/ZombieFemale/Walk (" + std::to_string(i) + ").png";
        auto tex = nu::Resources().Get<nu::Texture>(path, nu::Engine::Get().GetRenderer());
        m_femaleEnemyWalkFrames.push_back(tex);
    }

    m_femaleEnemyDeadFrames.clear();
    for (int i = 1; i <= 12; ++i)
    {
        std::string path = "Img/ZombieFemale/Dead (" + std::to_string(i) + ").png";
        auto tex = nu::Resources().Get<nu::Texture>(path, nu::Engine::Get().GetRenderer());
        m_femaleEnemyDeadFrames.push_back(tex);
    }

    nu::Engine::Get().GetAudio().AddSound("bgm", "audio/switch16.ogg");
    nu::Engine::Get().GetAudio().AddSound("punch", "audio/shoot-h.ogg");
    nu::Engine::Get().GetAudio().AddSound("defeat", "audio/explosion-c.ogg");
    nu::Engine::Get().GetAudio().AddSound("hurt", "audio/hurt-d.ogg");

    m_currentState = GameState::TitleScreen;
    m_player = { 100.0f, 500.0f, 50.0f, 60.0f, 250.0f, 1 };
    m_score = 0;
    m_health = 100;
    m_enemySpawnTimer = 0.0f;
    m_attackCooldown = 0.0f;
    m_enemyAnimTimer = 0.0f;
    m_enemyCurrentFrame = 0;
    m_playerAnimTimer = 0.0f;
    m_playerCurrentFrame = 0;
    m_isHurt = false;
    m_hurtAnimTimer = 0.0f;
    m_hurtCurrentFrame = 0;
    m_slideAnimTimer = 0.0f;
    m_slideCurrentFrame = 0;
    m_isAttacking = false;
    m_attackAnimTimer = 0.0f;

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
            m_player.x = 100.0f;
            m_player.y = 500.0f;
            m_player.facingRight = 1;
            m_enemies.clear();
            nu::Engine::Get().GetAudio().PlaySound("bgm");
        }
    }
    else if (m_currentState == GameState::InGame)
    {
        if (m_isHurt)
        {
            m_hurtAnimTimer += dt;
            if (m_hurtAnimTimer >= 0.08f)
            {
                m_hurtAnimTimer = 0.0f;
                m_hurtCurrentFrame++;
                if (m_hurtCurrentFrame >= m_playerHurtFrames.size())
                {
                    m_isHurt = false;
                    m_hurtCurrentFrame = 0;
                }
            }
        }
        else
        {
            bool isMoving = false;

            if (input.GetKeyDown(SDL_SCANCODE_W) || input.GetKeyDown(SDL_SCANCODE_UP))
            {
                m_player.y -= m_player.speed * dt;
                isMoving = true;
            }
            if (input.GetKeyDown(SDL_SCANCODE_S) || input.GetKeyDown(SDL_SCANCODE_DOWN))
            {
                m_player.y += m_player.speed * dt;
                isMoving = true;
            }
            if (input.GetKeyDown(SDL_SCANCODE_A) || input.GetKeyDown(SDL_SCANCODE_LEFT))
            {
                m_player.x -= m_player.speed * dt;
                m_player.facingRight = -1;
                isMoving = true;
            }
            if (input.GetKeyDown(SDL_SCANCODE_D) || input.GetKeyDown(SDL_SCANCODE_RIGHT))
            {
                m_player.x += m_player.speed * dt;
                m_player.facingRight = 1;
                isMoving = true;
            }

            if (m_player.x < 0) m_player.x = 0;
            if (m_player.x > 1024 - m_player.width) m_player.x = 1024 - m_player.width;
            if (m_player.y < 400) m_player.y = 400;
            if (m_player.y > 640 - m_player.height) m_player.y = 640 - m_player.height;

            if (isMoving)
            {
                m_playerAnimTimer += dt;
                if (m_playerAnimTimer >= 0.1f)
                {
                    m_playerAnimTimer = 0.0f;
                    if (!m_playerWalkFrames.empty())
                    {
                        m_playerCurrentFrame = (m_playerCurrentFrame + 1) % m_playerWalkFrames.size();
                    }
                }
            }
            else
            {
                m_playerCurrentFrame = 0;
            }
        }

        if (m_attackCooldown > 0) m_attackCooldown -= dt;

        if (m_attackAnimTimer > 0)
        {
            m_attackAnimTimer -= dt;
            m_slideAnimTimer += dt;
            if (m_slideAnimTimer >= 0.04f)
            {
                m_slideAnimTimer = 0.0f;
                if (!m_playerSlideFrames.empty())
                {
                    m_slideCurrentFrame = (m_slideCurrentFrame + 1) % m_playerSlideFrames.size();
                }
            }
        }
        else
        {
            m_isAttacking = false;
        }

        if (input.GetKeyPressed(SDL_SCANCODE_SPACE) && m_attackCooldown <= 0.0f && !m_isHurt)
        {
            m_isAttacking = true;
            m_attackAnimTimer = 0.4f;
            m_attackCooldown = 0.5f;
            m_slideCurrentFrame = 0;
            m_slideAnimTimer = 0.0f;
            nu::Engine::Get().GetAudio().PlaySound("punch");

            float slideHitboxX = (m_player.facingRight > 0) ? (m_player.x + m_player.width) : (m_player.x - 50.0f);
            Entity attackBox = { slideHitboxX, m_player.y, 50.0f, m_player.height, 0.0f, 1 };

            for (auto& enemy : m_enemies)
            {
                if (enemy.active && !enemy.isDead && enemy.Intersects(attackBox))
                {
                    enemy.isDead = true;
                    enemy.deathCurrentFrame = 0;
                    enemy.deathAnimTimer = 0.0f;
                    m_score += 150;
                    nu::Engine::Get().GetAudio().PlaySound("defeat");
                }
            }
        }

        m_enemyAnimTimer += dt;
        if (m_enemyAnimTimer >= 0.1f)
        {
            m_enemyAnimTimer = 0.0f;
            if (!m_enemyWalkFrames.empty())
            {
                m_enemyCurrentFrame = (m_enemyCurrentFrame + 1) % m_enemyWalkFrames.size();
            }
        }

        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0.0f)
        {
            float spawnX = (std::rand() % 2 == 0) ? -50.0f : 1024.0f;
            float spawnY = static_cast<float>(250 + (std::rand() % 300));

            int zombieType = std::rand() % 2;
            m_enemies.push_back({ spawnX, spawnY, 45.0f, 60.0f, 120.0f, 1, true, false, 0.0f, 0, zombieType });

            m_enemySpawnTimer = 1.5f;
        }

        for (auto it = m_enemies.begin(); it != m_enemies.end(); )
        {
            if (!it->active)
            {
                it = m_enemies.erase(it);
                continue;
            }

            if (it->isDead)
            {
                it->deathAnimTimer += dt;
                if (it->deathAnimTimer >= 0.06f)
                {
                    it->deathAnimTimer = 0.0f;
                    it->deathCurrentFrame++;

                    size_t deadFramesCount = (it->type == 1) ? m_femaleEnemyDeadFrames.size() : m_enemyDeadFrames.size();
                    if (it->deathCurrentFrame >= static_cast<int>(deadFramesCount))
                    {
                        it->active = false;
                    }
                }
            }
            else
            {
                if (it->x < m_player.x)
                {
                    it->x += it->speed * dt;
                    it->facingRight = 1;
                }
                else if (it->x > m_player.x)
                {
                    it->x -= it->speed * dt;
                    it->facingRight = -1;
                }

                if (it->y < m_player.y) it->y += (it->speed * 0.5f) * dt;
                if (it->y > m_player.y) it->y -= (it->speed * 0.5f) * dt;

                if (it->Intersects(m_player))
                {
                    it->active = false;
                    m_health -= 15;
                    nu::Engine::Get().GetAudio().PlaySound("hurt");

                    m_isHurt = true;
                    m_hurtCurrentFrame = 0;
                    m_hurtAnimTimer = 0.0f;

                    if (m_health <= 0)
                    {
                        m_currentState = GameState::GameOver;
                    }
                }
            }
            ++it;
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
    renderer.SetColor(20, 20, 30);
    renderer.Clear();

    if (m_backgroundTexture)
    {
        SDL_FRect bgRect = { 0.0f, 0.0f, 1024.0f, 720.0f };
        SDL_RenderTexture(renderer.GetRenderer(), m_backgroundTexture->GetTexture(), nullptr, &bgRect);
    }

    if (m_currentState == GameState::TitleScreen)
    {
        m_uiText->Create(renderer, "TOWN BRAWLER - PRESS SPACE TO START", { 1.0f, 1.0f, 1.0f, 1.0f });
        m_uiText->Draw(renderer, 220, 300);
    }
    else if (m_currentState == GameState::InGame)
    {
        SDL_FRect playerRect = { m_player.x, m_player.y, m_player.width, m_player.height };
        SDL_FlipMode playerFlip = (m_player.facingRight < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        if (m_isHurt && !m_playerHurtFrames.empty())
        {
            auto& hurtTex = m_playerHurtFrames[m_hurtCurrentFrame];
            if (hurtTex) SDL_RenderTextureRotated(renderer.GetRenderer(), hurtTex->GetTexture(), nullptr, &playerRect, 0.0, nullptr, playerFlip);
        }
        else if (m_isAttacking && !m_playerSlideFrames.empty())
        {
            auto& slideTex = m_playerSlideFrames[m_slideCurrentFrame];
            if (slideTex) SDL_RenderTextureRotated(renderer.GetRenderer(), slideTex->GetTexture(), nullptr, &playerRect, 0.0, nullptr, playerFlip);
        }
        else if (!m_playerWalkFrames.empty())
        {
            auto& walkTex = m_playerWalkFrames[m_playerCurrentFrame];
            if (walkTex) SDL_RenderTextureRotated(renderer.GetRenderer(), walkTex->GetTexture(), nullptr, &playerRect, 0.0, nullptr, playerFlip);
        }

        for (const auto& enemy : m_enemies)
        {
            if (!enemy.active) continue;

            SDL_FRect enemyRect = { enemy.x, enemy.y, enemy.width, enemy.height };
            SDL_FlipMode enemyFlip = (enemy.facingRight < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

            if (enemy.type == 1)
            {
                if (enemy.isDead && !m_femaleEnemyDeadFrames.empty())
                {
                    int frameIdx = std::min(enemy.deathCurrentFrame, static_cast<int>(m_femaleEnemyDeadFrames.size()) - 1);
                    auto& deadTex = m_femaleEnemyDeadFrames[frameIdx];
                    if (deadTex)
                    {
                        SDL_RenderTextureRotated(renderer.GetRenderer(), deadTex->GetTexture(), nullptr, &enemyRect, 0.0, nullptr, enemyFlip);
                    }
                }
                else if (!m_femaleEnemyWalkFrames.empty())
                {
                    int frameIdx = std::min(m_enemyCurrentFrame, static_cast<int>(m_femaleEnemyWalkFrames.size()) - 1);
                    auto& walkTex = m_femaleEnemyWalkFrames[frameIdx];
                    if (walkTex)
                    {
                        SDL_RenderTextureRotated(renderer.GetRenderer(), walkTex->GetTexture(), nullptr, &enemyRect, 0.0, nullptr, enemyFlip);
                    }
                }
            }
            else
            {
                if (enemy.isDead && !m_enemyDeadFrames.empty())
                {
                    int frameIdx = std::min(enemy.deathCurrentFrame, static_cast<int>(m_enemyDeadFrames.size()) - 1);
                    auto& deadTex = m_enemyDeadFrames[frameIdx];
                    if (deadTex)
                    {
                        SDL_RenderTextureRotated(renderer.GetRenderer(), deadTex->GetTexture(), nullptr, &enemyRect, 0.0, nullptr, enemyFlip);
                    }
                }
                else if (!m_enemyWalkFrames.empty())
                {
                    auto& walkTex = m_enemyWalkFrames[m_enemyCurrentFrame];
                    if (walkTex)
                    {
                        SDL_RenderTextureRotated(renderer.GetRenderer(), walkTex->GetTexture(), nullptr, &enemyRect, 0.0, nullptr, enemyFlip);
                    }
                }
            }
        }

        m_uiText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f, 1.0f });
        m_uiText->Draw(renderer, 20, 20);

        m_uiText->Create(renderer, "Health: " + std::to_string(m_health), { 0.2f, 1.0f, 0.2f, 1.0f });
        m_uiText->Draw(renderer, 20, 50);
    }
    else if (m_currentState == GameState::GameOver)
    {
        m_uiText->Create(renderer, "K.O. - GAME OVER", { 1.0f, 0.0f, 0.0f, 1.0f });
        m_uiText->Draw(renderer, 390, 250);

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