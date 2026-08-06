#include "../Engine/Engine.cpp"


int main() {
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1024, 720);
    std::shared_ptr<nu::Texture> texture = std::make_shared<nu::Texture>();
    texture->Load("Img/googly-a.png", renderer);

    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();
        renderer.DrawTexture(texture.get(), 300.0f, 200.0f);

        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}