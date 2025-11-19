#include "PCH.H"
#include "Terrarian.h"

Fance::Fance(const glm::vec3& position)
{
    m_model = std::make_shared<Model>("Models/fance.obj", "Models/Farm_texture.png");
    m_pos = position;
    m_rot = { 0.f, 180.f, 0.f };
    m_scale = { 1.f, 1.f, 1.f };
    m_name = "fence";
}

House::House(const glm::vec3& position)
{
    m_model = std::make_shared<Model>("Models/house.obj", "Models/Farm_texture.png");
    m_pos = position;
    m_rot = { 0.f, 0.f, 0.f };
    m_scale = { 1.f, 1.f, 1.f };
    m_name = "house";
}