#pragma once
#include "Model.h"

class GameObject
{
public:
    std::shared_ptr<Model> m_model;
    glm::vec3 m_pos;
    glm::vec3 m_rot;
    glm::vec3 m_scale;

	std::shared_ptr<class Collider> m_collider;
public:
    virtual ~GameObject() = default;
    virtual void Update(int time);
    virtual void Draw();
};