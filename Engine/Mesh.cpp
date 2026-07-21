#include "pch.h"
#include "Mesh.h"
#include "Renderer.h" 

namespace nu
{
    void Mesh::AddPoint(const Vector2& point)
    {
        m_points.push_back(point);
    }

    void Mesh::SetColor(uint8_t r, uint8_t g, uint8_t b)
    {
        m_r = r;
        m_g = g;
        m_b = b;
    }

    void Mesh::Draw(Renderer& renderer)
    {
        renderer.SetColor(m_r, m_g, m_b);

        if (m_points.size() > 1)
        {
            for (size_t i = 0; i < m_points.size() - 1; i++)
            {
                renderer.DrawLine(
                    m_points[i].x, m_points[i].y,
                    m_points[i + 1].x, m_points[i + 1].y
                );
            }

            renderer.DrawLine(
                m_points.back().x, m_points.back().y,
                m_points.front().x, m_points.front().y
            );
        }
    }
}