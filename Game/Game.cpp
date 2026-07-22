#include "../Engine/Engine.cpp" 

int main() {
    nu::Renderer renderer;
    renderer.Initialize("Nu Game Engine - Vector Cat & Soundboard", 1024, 720);

    nu::Input input;

    FMOD::System* audio = nullptr;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;
    FMOD::Sound* sound = nullptr;

    audio->createSound("mario.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("hee-hee.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

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

        input.Update();

        if (input.GetKeyPressed(SDL_SCANCODE_1)) audio->playSound(sounds[0], nullptr, false, nullptr);
        if (input.GetKeyPressed(SDL_SCANCODE_2)) audio->playSound(sounds[1], nullptr, false, nullptr);
        if (input.GetKeyPressed(SDL_SCANCODE_3)) audio->playSound(sounds[2], nullptr, false, nullptr);
        if (input.GetKeyPressed(SDL_SCANCODE_4)) audio->playSound(sounds[3], nullptr, false, nullptr);
        if (input.GetKeyPressed(SDL_SCANCODE_5)) audio->playSound(sounds[4], nullptr, false, nullptr);

        audio->update();

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        renderer.Present();
    }

    for (FMOD::Sound* s : sounds)
    {
        s->release();
    }
    audio->close();
    audio->release();

    renderer.Shutdown();

    return 0;
}