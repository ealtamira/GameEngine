#include "pch.h"
#include "Model.h"
#include "Renderer.h"

namespace nu
{
    void Model::AddMesh(const Mesh& mesh)
    {
        m_meshes.push_back(mesh);
    }

    void Model::Draw(Renderer& renderer)
    {
        for (Mesh& mesh : m_meshes)
        {
            mesh.Draw(renderer);
        }
    }
}