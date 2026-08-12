#include "../Engine/Engine.h"

int main() {
    nu::Engine::Get().Initialize();

    std::cout << "--- Game Engine Factory Test ---" << std::endl;
    Factory::Instance().Register("ScreenshotPlayer", std::make_unique<Creator<Player>>());

    Object* myObject = Factory::Instance().Create("ScreenshotPlayer");

    Actor* myActor = dynamic_cast<Actor*>(myObject);
    if (myActor)
    {
        myActor->Initialize();

        std::cout << "IsActor: " << (myActor->IsActor ? "True" : "False") << std::endl;
        std::cout << "Radius: " << myActor->GetRadius() << std::endl;
    }

    delete myObject;
    nu::Engine::Get().Shutdown();

    return 0;
}