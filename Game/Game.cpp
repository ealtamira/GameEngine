#include "../Engine/pch.h"
#include "../Engine/Engine.h"
#include "../Engine/Resources/ResourceManager.h"
#include "../Engine/Core/File.h"
#include "../Game/SpriteGame/SpriteGame.h"
#include <memory>
#include <vector>

int main()
{
    auto& renderer = nu::Engine::Get().GetRenderer();
    renderer.Initialize("Nu Game Engine - Town Brawler", 1024, 720);

    nu::Engine::Get().Initialize();

    const std::string startupDir = nu::GetWorkingDirectory();
    auto tryAssetRoot = [&](const std::string& path)
        {
            nu::SetWorkingDirectory(startupDir);
            if (!nu::SetWorkingDirectory(path)) return false;
            return nu::FileExists("Img/BG.png") && nu::FileExists("fonts/Western.ttf");
        };

    if (!tryAssetRoot("."))
    {
        const std::vector<std::string> candidates = {
            "Assets/SpriteGame",
            "Build/Assets/SpriteGame",
            "../Build/Assets/SpriteGame",
            "../../Build/Assets/SpriteGame",
            "Build"
        };

        for (const auto& candidate : candidates)
        {
            if (tryAssetRoot(candidate)) break;
        }
    }

    std::unique_ptr<SpriteGame> game = std::make_unique<SpriteGame>();
    game->Initialize();

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

        nu::Engine::Get().Update(dt);

        game->Update(dt);

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        game->Draw(renderer);

        renderer.Present();
    }

    game.reset();

    nu::Resources().RemoveAll();
    nu::Engine::Get().Shutdown();
    renderer.Shutdown();

    return 0;
}