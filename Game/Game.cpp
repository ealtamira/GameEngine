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
    player->AddComponent<TransformComponent>(512.0f, 360.0f);
    player->AddComponent<SpriteRendererComponent>(playerTexture, &renderer);
    auto* playerRb = player->AddComponent<RigidBodyComponent>(0.0f, 0.0f);
    auto* playerCollider = player->AddComponent<CircleColliderComponent>(20.0f);

    float playerSpeed = 300.0f;

    int score = 0;
    int health = 100;

    struct EntityObject {
        std::unique_ptr<Actor> actor;
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
                if (auto* transform = player->GetComponent<TransformComponent>())
                {
                    transform->x = 512.0f;
                    transform->y = 360.0f;
                }
                activeBullets.clear();
                activeEnemies.clear();

                nu::Engine::Get().GetAudio().PlaySound("bgm");
            }
        }
        else if (currentState == GameState::InGame)
        {
            float playerX = 0.0f;
            float playerY = 0.0f;
            if (auto* transform = player->GetComponent<TransformComponent>())
            {
                playerX = transform->x;
                playerY = transform->y;

                if (input.GetKeyDown(SDL_SCANCODE_W)) playerY -= playerSpeed * dt;
                if (input.GetKeyDown(SDL_SCANCODE_S)) playerY += playerSpeed * dt;
                if (input.GetKeyDown(SDL_SCANCODE_A)) playerX -= playerSpeed * dt;
                if (input.GetKeyDown(SDL_SCANCODE_D)) playerX += playerSpeed * dt;

                if (playerX < 0) playerX = 0;
                if (playerX > 1024 - 40) playerX = 1024 - 40;
                if (playerY < 0) playerY = 0;
                if (playerY > 720 - 40) playerY = 720 - 40;

                transform->x = playerX;
                transform->y = playerY;
            }

            if (shootCooldown > 0) shootCooldown -= dt;
            if (input.GetKeyPressed(SDL_SCANCODE_SPACE) && shootCooldown <= 0.0f)
            {
                auto bulletActor = std::make_unique<Actor>();
                bulletActor->AddComponent<TransformComponent>(playerX + 15.0f, playerY - 10.0f);
                bulletActor->AddComponent<SpriteRendererComponent>(bulletTexture, &renderer);
                bulletActor->AddComponent<RigidBodyComponent>(0.0f, -500.0f);
                bulletActor->AddComponent<CircleColliderComponent>(5.0f);

                activeBullets.push_back({ std::move(bulletActor) });

                nu::Engine::Get().GetAudio().PlaySound("shoot");
                shootCooldown = 0.25f;
            }

            for (auto& b : activeBullets)
            {
                b.actor->Update(dt);
            }

            activeBullets.erase(
                std::remove_if(activeBullets.begin(), activeBullets.end(), [](const EntityObject& b) {
                    if (auto* transform = b.actor->GetComponent<TransformComponent>())
                    {
                        return transform->y < -20.0f;
                    }
                    return true;
                    }),
                activeBullets.end()
            );

            enemySpawnTimer -= dt;
            if (enemySpawnTimer <= 0.0f)
            {
                float randomX = static_cast<float>(std::rand() % 980);
                auto enemyActor = std::make_unique<Actor>();
                enemyActor->AddComponent<TransformComponent>(randomX, -50.0f);
                enemyActor->AddComponent<SpriteRendererComponent>(enemyTexture, &renderer);
                enemyActor->AddComponent<RigidBodyComponent>(0.0f, 150.0f);
                enemyActor->AddComponent<CircleColliderComponent>(20.0f);

                activeEnemies.push_back({ std::move(enemyActor) });
                enemySpawnTimer = 1.0f;
            }

            for (auto& en : activeEnemies)
            {
                en.actor->Update(dt);
            }

            activeEnemies.erase(
                std::remove_if(activeEnemies.begin(), activeEnemies.end(), [](const EntityObject& en) {
                    if (auto* transform = en.actor->GetComponent<TransformComponent>())
                    {
                        return transform->y > 740.0f;
                    }
                    return true;
                    }),
                activeEnemies.end()
            );

            float playerXCoord = 0.0f, playerYCoord = 0.0f;
            if (auto* transform = player->GetComponent<TransformComponent>())
            {
                playerXCoord = transform->x;
                playerYCoord = transform->y;
            }

            for (auto it = activeEnemies.begin(); it != activeEnemies.end(); )
            {
                float enemyX = 0.0f, enemyY = 0.0f;
                if (auto* transform = it->actor->GetComponent<TransformComponent>())
                {
                    enemyX = transform->x;
                    enemyY = transform->y;
                }

                float dx = playerXCoord - enemyX;
                float dy = playerYCoord - enemyY;
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
                float bulletX = 0.0f, bulletY = 0.0f;
                if (auto* transform = bulletIt->actor->GetComponent<TransformComponent>())
                {
                    bulletX = transform->x;
                    bulletY = transform->y;
                }

                for (auto enemyIt = activeEnemies.begin(); enemyIt != activeEnemies.end(); )
                {
                    float enemyX = 0.0f, enemyY = 0.0f;
                    if (auto* transform = enemyIt->actor->GetComponent<TransformComponent>())
                    {
                        enemyX = transform->x;
                        enemyY = transform->y;
                    }

                    float dx = bulletX - enemyX;
                    float dy = bulletY - enemyY;
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
            player->Draw();

            for (const auto& b : activeBullets)
            {
                b.actor->Draw();
            }

            for (const auto& en : activeEnemies)
            {
                en.actor->Draw();
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