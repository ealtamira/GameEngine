#include "../Engine/Engine.cpp"

int main() {
    nu::Renderer renderer;
	renderer.Initialize("Game Engine", 1024, 720);

	nu::Input input;
    SDL_Event e;
    bool quit = false;

    std::vector<nu::Vector2> points;

    while (!quit) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
        }

		input.Update();

        if (input.GetButtonDown(nu::Input::MouseButton::Left))
        {
            nu::Vector2 position = input.GetMousePosition();

            if (points.empty())
            {
                points.push_back(position);
            }
            else
            {
                nu::Vector2 lastPoint = points.back();
                nu::Vector2 difference = position - lastPoint;

                if (difference.Length() > 10.0f)
                {
                    points.push_back(position);
                }
            }
        }


		renderer.SetColor(0, 0, 0);
		renderer.Clear();

        renderer.SetColor(255, 255, 255);

        if (points.size() > 1)
        {
            for (size_t i = 0; i < points.size() - 1; i++)
            {
                renderer.DrawLine(
                    points[i].x, points[i].y,
                    points[i + 1].x, points[i + 1].y
                );
            }
        }

        /*for (int i = 0; i < 20; i++)
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
        }*/

		renderer.Present();
    }

	renderer.Shutdown();

    return 0;
}