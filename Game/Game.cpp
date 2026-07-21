#include "../Engine/Engine.cpp" 
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    nu::Renderer renderer;
    renderer.Initialize("Nu Game Engine - Vector Cat", 1024, 720);

    SDL_Event e;
    bool quit = false;

    nu::Model catModel;

    nu::Mesh headMesh;

    headMesh.AddPoint(nu::Vector2(200, 350)); 
    headMesh.AddPoint(nu::Vector2(150, 350)); 
    headMesh.AddPoint(nu::Vector2(150, 280)); 
    headMesh.AddPoint(nu::Vector2(120, 230)); 
    headMesh.AddPoint(nu::Vector2(180, 280)); 
    headMesh.AddPoint(nu::Vector2(220, 280)); 
    headMesh.AddPoint(nu::Vector2(190, 230)); 
    headMesh.AddPoint(nu::Vector2(250, 280)); 
    headMesh.AddPoint(nu::Vector2(300, 330)); 
    headMesh.AddPoint(nu::Vector2(250, 400)); 
    headMesh.AddPoint(nu::Vector2(200, 350)); 


    headMesh.SetColor(255, 215, 0);
    catModel.AddMesh(headMesh);

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

        catModel.Draw(renderer);
        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}