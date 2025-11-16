#include "PCH.H"
#include "House.h"

House::House()
{
    m_model = std::make_shared<Model>("Models/farm.obj");
    m_pos = { 0.f, 0.f, 0.f };
    m_rot = { 0.f, 0.f, 0.f };
    m_scale = { 1.f, 1.f, 1.f };
}