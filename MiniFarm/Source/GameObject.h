#pragma once
#include "Model.h"

class GameObject
{
public:
    std::shared_ptr<Model> m_model;
    glm::vec3 m_pos;
    glm::vec3 m_rot;
    glm::vec3 m_scale;

    bool m_alive = false;
	std::string m_name = ""; // for debug
	std::shared_ptr<class Collider> m_collider;
public:
    virtual ~GameObject() = default;

    virtual void Init();
    virtual void Update(int time);
    virtual void Draw();
    virtual void DebugDraw();
	
    virtual void OnCollision(GameObject* other) {}
};