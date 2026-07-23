#include "../Engine/Engine.cpp" 

int main() {
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    if (!filenames.empty())
    {
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    nu::Renderer renderer;
    renderer.Initialize("Nu Game Engine - File System & Soundboard", 1024, 720);

    nu::Input input;

    FMOD::System* audio = nullptr;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;
    FMOD::Sound* sound = nullptr;

    audio->createSound("kick.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("hihat.wav", FMOD_DEFAULT, 0, &sound);
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