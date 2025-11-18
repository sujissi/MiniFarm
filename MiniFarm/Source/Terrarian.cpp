#include "PCH.H"
#include "Terrarian.h"

Fance::Fance(const glm::vec3& position)
{
    m_model = std::make_shared<Model>("Models/fance.obj");
    m_pos = position;
    m_rot = { 0.f, 180.f, 0.f };
    m_scale = { 1.f, 1.f, 1.f };
}

House::House(const glm::vec3& position)
{
    m_model = std::make_shared<Model>("Models/house.obj");
    m_pos = position;
    m_rot = { 0.f, 0.f, 0.f };
    m_scale = { 1.f, 1.f, 1.f };
}