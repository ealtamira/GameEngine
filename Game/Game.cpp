#include "../Engine/Engine.cpp"


int main() {
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1024, 720);

    TTF_Init();

    auto texture = nu::Resources().Get<nu::Texture>("Img/googly-a.png", renderer);

    auto font = nu::Resources().GetWithID<nu::Font>("title_font", "fonts/airstrike.ttf", 64.0f);
    nu::Text titleText(font);

    nu::Color textColor = { 255.0f, 255.0f, 255.0f }; // White text
    titleText.Create(renderer, "Resource Manager Complete!", textColor);

    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        renderer.DrawTexture(texture.get(), 300.0f, 200.0f);

        titleText.Draw(renderer, 300.0f, 100.0f);

        renderer.Present();
    }

    nu::Resources().RemoveAll();
    renderer.Shutdown();
    TTF_Quit();

    return 0;
}