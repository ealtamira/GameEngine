#pragma once
#include <vector>
#include "Mesh.h"

namespace nu
{
    class Model
    {
    public:
        void AddMesh(const Mesh& mesh);

        void Draw(class Renderer& renderer);

    private:
        std::vector<Mesh> m_meshes;
    };
}