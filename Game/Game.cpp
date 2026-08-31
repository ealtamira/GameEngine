#include "../Engine/pch.h"
#include "../Engine/Engine.h"
#include "../Engine/Input/Input.h"
#include "../Engine/Resources/ResourceManager.h"
#include "../Engine/Renderer/Font.h"
#include "../Engine/Renderer/Text.h"
#include "../Engine/Renderer/Texture.h"
#include "../Engine/Framework/Actor.h"
#include "../Engine/Framework/TransformComponent.h"
#include "../Engine/TextureFrames.h"
#include "../Engine/SpriteAnimationRendererComponent.h"
#include "../Engine/Tilemap.h"
#include "../Engine/Framework/TilemapRendererComponent.h"

int main()
{
    nu::Renderer renderer;
    renderer.Initialize("Nu Game Engine - Tilemap Test", 1024, 720);

    nu::Input input;
    nu::Engine::Get().Initialize();

    auto mapTilemap = nu::Resources().Get<nu::Tilemap>("map.json", renderer);
    if (!mapTilemap)
    {
        SDL_Log("CRITICAL: Failed to load map.json!");
    }

    auto mapActor = std::make_unique<Actor>();
    mapActor->AddComponent<TransformComponent>(0.0f, 0.0f);
    auto* tilemapRenderer = mapActor->AddComponent<nu::TilemapRendererComponent>();
    tilemapRenderer->SetRenderer(&renderer);
    tilemapRenderer->SetTilemap(mapTilemap);

    SDL_Event e;
    bool quit = false;
    Uint32 prevTime = SDL_GetTicks();

    while (!quit)
    {
        Uint32 currTime = SDL_GetTicks();
        float dt = static_cast<float>(currTime - prevTime) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        prevTime = currTime;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT || (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE))
            {
                quit = true;
            }
        }

        input.Update();
        nu::Engine::Get().Update(dt);

        mapActor->Update(dt);

        renderer.SetColor(30, 30, 40);
        renderer.Clear();

        mapActor->Draw();

        renderer.Present();
    }

    nu::Resources().RemoveAll();
    nu::Engine::Get().Shutdown();
    renderer.Shutdown();

    return 0;
}