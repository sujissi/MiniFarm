#include "PCH.H"
#include "landform.h"

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

Ground::Ground(const glm::vec3& position)
{
    m_model = std::make_shared<Model>("Models/landform.obj", "Models/Farm_texture.png");
    m_pos = position;
    m_rot = { 0.f, 0.f, 0.f };
    m_scale = { 1.f, 1.f, 1.f };
    m_name = "ground";
}

Tree::Tree(const glm::vec3& position)
{
    m_model = std::make_shared<Model>("Models/tree.obj", "Models/Farm_texture.png");
    m_pos = position;
    m_rot = { 0.f, 0.f, 0.f };
    m_scale = { 1.f, 1.f, 1.f };
    m_name = "tree";
}

Boat::Boat(const glm::vec3& position)
{
    m_model = std::make_shared<Model>("Models/boat.obj", "Models/boat.png");
    m_pos = position;
    m_rot = { 0.f, 0.f, 0.f };
    m_scale = { 1.f, 1.f, 1.f };
    m_name = "boat";
}