#include "../Engine/Engine.h"

int main()
{
    nu::Engine::Get().Initialize();

    std::string name;
    int age;
    float speed;
    bool isAwake;
    nu::Vector2 position;
    nu::Vector3 color;

    rapidjson::Document document;
    if (nu::json::Load("data.json", document))
    {
        nu::json::Read(document, "name", name);
        nu::json::Read(document, "age", age);
        nu::json::Read(document, "speed", speed);
        nu::json::Read(document, "isAwake", isAwake);
        nu::json::Read(document, "position", position);
        nu::json::Read(document, "color", color);

        std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
        std::cout << position.x << " " << position.y << std::endl;
        std::cout << color.x << " " << color.y << " " << color.z << std::endl;
    }

    nu::Engine::Get().Shutdown();

    return 0;
}