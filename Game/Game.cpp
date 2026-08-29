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

int main()
{
    nu::Renderer renderer;
    renderer.Initialize("Nu Game Engine - Animation Test", 1024, 720);

    nu::Input input;
    nu::Engine::Get().Initialize();

    auto enemyAnimTexture = nu::Resources().Get<nu::Texture>("Img/reaper-sprite.png", renderer);
    if (!enemyAnimTexture || !enemyAnimTexture->GetTexture())
    {
        SDL_Log("Failed to load reaper-sprite.png!");
    }

    auto enemyTextureFrames = std::make_shared<nu::TextureFrames>(enemyAnimTexture.get());

    for (int i = 0; i < 7; ++i) {
        enemyTextureFrames->AddFrame({ i * 64, 0, 64, 64 });
    }

    auto animatedActor = std::make_unique<Actor>();
    animatedActor->AddComponent<TransformComponent>(512.0f, 360.0f);
    animatedActor->scale = 3.0f;

    auto* animRenderer = animatedActor->AddComponent<nu::SpriteAnimationRendererComponent>();
    animRenderer->SetTextureFrames(enemyTextureFrames, 0.15f);
    animRenderer->SetRenderer(&renderer);

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

        animatedActor->Update(dt);

        renderer.SetColor(30, 30, 40);
        renderer.Clear();

        animatedActor->Draw();

        renderer.Present();
    }

    nu::Resources().RemoveAll();
    nu::Engine::Get().Shutdown();
    renderer.Shutdown();

    return 0;
}