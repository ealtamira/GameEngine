#include "../Engine/Engine.cpp"
 
#include <iostream>


int main() {
    nu::Renderer renderer;
	renderer.Initialize("Game Engine", 1024, 720);

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

        for (int i = 0; i < 20; i++)
        {
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
			renderer.DrawPoint(rand() % 1024, rand() % 720);
        }

        for (int i = 0; i < 10; i++) 
        {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawLine(rand() % 1024, rand() % 720, rand() % 1024, rand() % 720);
        }

        for (int i = 0; i < 10; i++)
        {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawFillRect(rand() % 400, rand() % 400, rand() % 50, rand() % 50);
        }

		renderer.Present();
    }

	renderer.Shutdown();

    return 0;
}