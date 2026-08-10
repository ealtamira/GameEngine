#include "../Engine/Engine.cpp"


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

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    nu::Renderer renderer;
    renderer.Initialize("Nu Game Engine - Remastered", 1024, 720);

    nu::Input input;
    nu::Engine::Get().Initialize();

    TTF_Init();

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

    Entity player = { 512.0f, 360.0f, 40.0f, 40.0f, 300.0f, true };
    int score = 0;
    int health = 100;

    std::vector<Entity> enemies;
    std::vector<Entity> bullets;
    std::vector<Entity> pickups;

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
                player.x = 512.0f;
                player.y = 360.0f;
                enemies.clear();
                bullets.clear();
                pickups.clear();

                nu::Engine::Get().GetAudio().PlaySound("bgm");
            }
        }
        else if (currentState == GameState::InGame)
        {
            if (input.GetKeyDown(SDL_SCANCODE_W)) player.y -= player.speed * dt;
            if (input.GetKeyDown(SDL_SCANCODE_S)) player.y += player.speed * dt;
            if (input.GetKeyDown(SDL_SCANCODE_A)) player.x -= player.speed * dt;
            if (input.GetKeyDown(SDL_SCANCODE_D)) player.x += player.speed * dt;

            if (player.x < 0) player.x = 0;
            if (player.x > 1024 - player.width) player.x = 1024 - player.width;
            if (player.y < 0) player.y = 0;
            if (player.y > 720 - player.height) player.y = 720 - player.height;

            if (shootCooldown > 0) shootCooldown -= dt;
            if (input.GetKeyPressed(SDL_SCANCODE_SPACE) && shootCooldown <= 0.0f)
            {
                bullets.push_back({ player.x + 15.0f, player.y - 10.0f, 10.0f, 20.0f, 500.0f, true });
                nu::Engine::Get().GetAudio().PlaySound("shoot");
                shootCooldown = 0.25f;
            }

            for (auto& bullet : bullets)
            {
                if (bullet.active)
                {
                    bullet.y -= bullet.speed * dt;
                    if (bullet.y < 0) bullet.active = false;
                }
            }

            enemySpawnTimer -= dt;
            if (enemySpawnTimer <= 0.0f)
            {
                float randomX = static_cast<float>(std::rand() % 980);
                enemies.push_back({ randomX, -50.0f, 40.0f, 40.0f, 150.0f, true });
                enemySpawnTimer = 1.0f;
            }

            for (auto& enemy : enemies)
            {
                if (!enemy.active) continue;

                enemy.y += enemy.speed * dt;

                for (auto& bullet : bullets)
                {
                    if (bullet.active && enemy.Intersects(bullet))
                    {
                        enemy.active = false;
                        bullet.active = false;
                        score += 100;
                        nu::Engine::Get().GetAudio().PlaySound("explosion");

                        if (std::rand() % 100 < 15)
                        {
                            pickups.push_back({ enemy.x, enemy.y, 25.0f, 25.0f, 50.0f, true });
                        }
                    }
                }

                if (enemy.Intersects(player))
                {
                    enemy.active = false;
                    health -= 20;
                    nu::Engine::Get().GetAudio().PlaySound("player_hit");
                    if (health <= 0)
                    {
                        currentState = GameState::GameOver;
                    }
                }

                if (enemy.y > 720) enemy.active = false;
            }

            for (auto& pickup : pickups)
            {
                if (!pickup.active) continue;
                pickup.y += pickup.speed * dt;

                if (pickup.Intersects(player))
                {
                    pickup.active = false;
                    health += 20;
                    if (health > 100) health = 100;
                    nu::Engine::Get().GetAudio().PlaySound("pickup");
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
            if (playerTexture) renderer.DrawTexture(playerTexture.get(), player.x, player.y);

            for (const auto& bullet : bullets)
            {
                if (bullet.active && bulletTexture)
                {
                    renderer.DrawTexture(bulletTexture.get(), bullet.x, bullet.y);
                }
            }

            for (const auto& enemy : enemies)
            {
                if (enemy.active && enemyTexture)
                {
                    renderer.DrawTexture(enemyTexture.get(), enemy.x, enemy.y);
                }
            }

            for (const auto& pickup : pickups)
            {
                if (pickup.active && pickupTexture)
                {
                    renderer.DrawTexture(pickupTexture.get(), pickup.x, pickup.y);
                }
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