#include "../Engine/Engine.cpp"

enum class GameState
{
    TitleScreen,
    InGame,
    GameOver
};

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    nu::Renderer renderer;
    renderer.Initialize("Nu Game Engine - Component Architecture", 1024, 720);

    nu::Input input;
    nu::Engine::Get().Initialize();

    if (!TTF_Init()) {
    }

    auto font = nu::Resources().GetWithID<nu::Font>("ui_font", "fonts/Western.ttf", 24.0f);
    nu::Text uiText(font);

    auto backgroundTexture = nu::Resources().Get<nu::Texture>("Img/darkPurple.png", renderer);
    auto playerTexture = nu::Resources().Get<nu::Texture>("Img/player.png", renderer);
    auto enemyTexture = nu::Resources().Get<nu::Texture>("Img/enemy.png", renderer);
    auto bulletTexture = nu::Resources().Get<nu::Texture>("Img/bullet.png", renderer);
    auto pickupTexture = nu::Resources().Get<nu::Texture>("Img/pickup.png", renderer);

    nu::Engine::Get().GetAudio().AddSound("bgm", "assets/switch16.ogg");
    nu::Engine::Get().GetAudio().AddSound("shoot", "assets/shoot-h.ogg");
    nu::Engine::Get().GetAudio().AddSound("explosion", "assets/explosion-c.ogg");
    nu::Engine::Get().GetAudio().AddSound("pickup", "assets/coin-c.ogg");
    nu::Engine::Get().GetAudio().AddSound("player_hit", "assets/hurt-d.ogg");

    GameState currentState = GameState::TitleScreen;

    auto player = std::make_unique<Actor>();
    auto* playerRb = player->AddComponent<RigidBodyComponent>(0.0f, 0.0f);
    auto* playerCollider = player->AddComponent<CircleColliderComponent>(20.0f);

    float playerX = 512.0f, playerY = 360.0f;
    float playerSpeed = 300.0f;

    int score = 0;
    int health = 100;

    std::vector<std::unique_ptr<Actor>> enemies;
    std::vector<std::unique_ptr<Actor>> bullets;
    std::vector<std::unique_ptr<Actor>> pickups;

    struct EntityObject {
        std::unique_ptr<Actor> actor;
        float x, y;
    };

    std::vector<EntityObject> activeBullets;
    std::vector<EntityObject> activeEnemies;

    float enemySpawnTimer = 0.0f;
    float shootCooldown = 0.0f;

    SDL_Event e;
    bool quit = false;
    Uint32 prevTime = SDL_GetTicks();

    while (!quit)
    {
        Uint32 currTime = SDL_GetTicks();
        float dt = (currTime - prevTime) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        prevTime = currTime;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        input.Update();
        nu::Engine::Get().Update(dt);

        if (currentState == GameState::TitleScreen)
        {
            if (input.GetKeyPressed(SDL_SCANCODE_SPACE))
            {
                currentState = GameState::InGame;
                score = 0;
                health = 100;
                playerX = 512.0f;
                playerY = 360.0f;
                enemies.clear();
                bullets.clear();
                pickups.clear();
                activeBullets.clear();
                activeEnemies.clear();

                nu::Engine::Get().GetAudio().PlaySound("bgm");
            }
        }
        else if (currentState == GameState::InGame)
        {
            if (input.GetKeyDown(SDL_SCANCODE_W)) playerY -= playerSpeed * dt;
            if (input.GetKeyDown(SDL_SCANCODE_S)) playerY += playerSpeed * dt;
            if (input.GetKeyDown(SDL_SCANCODE_A)) playerX -= playerSpeed * dt;
            if (input.GetKeyDown(SDL_SCANCODE_D)) playerX += playerSpeed * dt;

            if (playerX < 0) playerX = 0;
            if (playerX > 1024 - 40) playerX = 1024 - 40;
            if (playerY < 0) playerY = 0;
            if (playerY > 720 - 40) playerY = 720 - 40;

            if (shootCooldown > 0) shootCooldown -= dt;
            if (input.GetKeyPressed(SDL_SCANCODE_SPACE) && shootCooldown <= 0.0f)
            {
                auto bulletActor = std::make_unique<Actor>();
                bulletActor->AddComponent<RigidBodyComponent>(0.0f, -500.0f);
                bulletActor->AddComponent<CircleColliderComponent>(5.0f);

                activeBullets.push_back({ std::move(bulletActor), playerX + 15.0f, playerY - 10.0f });

                nu::Engine::Get().GetAudio().PlaySound("shoot");
                shootCooldown = 0.25f;
            }

            for (auto& b : activeBullets)
            {
                b.actor->Update(dt);
                if (auto* rb = b.actor->GetComponent<RigidBodyComponent>())
                {
                    b.y += rb->velocityY * dt;
                }
            }

            activeBullets.erase(
                std::remove_if(activeBullets.begin(), activeBullets.end(), [](const EntityObject& b) {
                    return b.y < -20.0f;
                    }),
                activeBullets.end()
            );

            enemySpawnTimer -= dt;
            if (enemySpawnTimer <= 0.0f)
            {
                float randomX = static_cast<float>(std::rand() % 980);
                auto enemyActor = std::make_unique<Actor>();
                enemyActor->AddComponent<RigidBodyComponent>(0.0f, 150.0f);
                enemyActor->AddComponent<CircleColliderComponent>(20.0f);

                activeEnemies.push_back({ std::move(enemyActor), randomX, -50.0f });
                enemySpawnTimer = 1.0f;
            }

            for (auto& en : activeEnemies)
            {
                en.actor->Update(dt);
                if (auto* rb = en.actor->GetComponent<RigidBodyComponent>())
                {
                    en.y += rb->velocityY * dt;
                }
            }

            activeEnemies.erase(
                std::remove_if(activeEnemies.begin(), activeEnemies.end(), [](const EntityObject& en) {
                    return en.y > 740.0f;
                    }),
                activeEnemies.end()
            );

            for (auto it = activeEnemies.begin(); it != activeEnemies.end(); )
            {
                float dx = playerX - it->x;
                float dy = playerY - it->y;
                float distanceSquared = (dx * dx) + (dy * dy);
                float collisionRadius = 20.0f + 20.0f;

                if (distanceSquared < (collisionRadius * collisionRadius))
                {
                    health -= 10;
                    nu::Engine::Get().GetAudio().PlaySound("player_hit");

                    if (health <= 0)
                    {
                        currentState = GameState::GameOver;
                        nu::Engine::Get().GetAudio().PlaySound("explosion");
                    }

                    it = activeEnemies.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            for (auto bulletIt = activeBullets.begin(); bulletIt != activeBullets.end(); )
            {
                bool bulletHit = false;

                for (auto enemyIt = activeEnemies.begin(); enemyIt != activeEnemies.end(); )
                {
                    float dx = bulletIt->x - enemyIt->x;
                    float dy = bulletIt->y - enemyIt->y;
                    float distanceSquared = (dx * dx) + (dy * dy);
                    float collisionRadius = 5.0f + 20.0f;

                    if (distanceSquared < (collisionRadius * collisionRadius))
                    {
                        score += 100;
                        nu::Engine::Get().GetAudio().PlaySound("explosion");

                        enemyIt = activeEnemies.erase(enemyIt);
                        bulletHit = true;
                        break;
                    }
                    else
                    {
                        ++enemyIt;
                    }
                }

                if (bulletHit)
                {
                    bulletIt = activeBullets.erase(bulletIt);
                }
                else
                {
                    ++bulletIt;
                }
            }
        }
        else if (currentState == GameState::GameOver)
        {
            if (input.GetKeyPressed(SDL_SCANCODE_R))
            {
                currentState = GameState::TitleScreen;
            }
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        if (backgroundTexture)
        {
            SDL_FRect bgRect = { 0.0f, 0.0f, 1024.0f, 720.0f };
            SDL_RenderTexture(renderer.GetRenderer(), backgroundTexture->GetTexture(), nullptr, &bgRect);
        }

        if (currentState == GameState::TitleScreen)
        {
            uiText.Create(renderer, "ARENA SHOOTER - PRESS SPACE TO START", { 1.0f, 1.0f, 1.0f });
            uiText.Draw(renderer, 250, 300);
        }
        else if (currentState == GameState::InGame)
        {
            if (playerTexture) renderer.DrawTexture(playerTexture.get(), playerX, playerY);

            for (const auto& b : activeBullets)
            {
                if (bulletTexture) renderer.DrawTexture(bulletTexture.get(), b.x, b.y);
            }

            for (const auto& en : activeEnemies)
            {
                if (enemyTexture) renderer.DrawTexture(enemyTexture.get(), en.x, en.y);
            }

            uiText.Create(renderer, "Score: " + std::to_string(score), { 1.0f, 1.0f, 1.0f });
            uiText.Draw(renderer, 20, 20);

            uiText.Create(renderer, "Health: " + std::to_string(health), { 0.2f, 1.0f, 0.2f });
            uiText.Draw(renderer, 20, 50);
        }
        else if (currentState == GameState::GameOver)
        {
            uiText.Create(renderer, "GAME OVER", { 1.0f, 0.0f, 0.0f });
            uiText.Draw(renderer, 400, 250);

            uiText.Create(renderer, "Final Score: " + std::to_string(score), { 1.0f, 1.0f, 1.0f });
            uiText.Draw(renderer, 380, 300);

            uiText.Create(renderer, "PRESS R TO RESTART", { 1.0f, 1.0f, 1.0f });
            uiText.Draw(renderer, 350, 350);
        }

        renderer.Present();
    }

    nu::Resources().RemoveAll();

    nu::Engine::Get().Shutdown();
    renderer.Shutdown();

    TTF_Quit();

    return 0;
}