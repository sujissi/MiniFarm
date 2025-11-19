#include "PCH.h"
#include "CollisionSystem.h"
#include "SceneManager.h"
#include "Collider.h"

glm::vec3 CollisionSystem::TryMove(GameObject* obj, const glm::vec3& desiredPos)
{
    auto& objects = SceneManager::GetObjects();

    if (!obj->m_collider)
        return desiredPos;

    glm::vec3 oldPos = obj->m_pos;
    glm::vec3 newPos = desiredPos;

    obj->m_pos = glm::vec3(desiredPos.x, oldPos.y, oldPos.z);
    obj->m_collider->UpdatePos(obj->m_pos);

    for (auto& other : objects)
    {
        if (other.get() == obj || !other->m_collider) continue;
        if (obj->m_collider->Intersects(other->m_collider.get()))
        {
            newPos.x = oldPos.x;
            break;
        }
    }

    obj->m_pos = glm::vec3(newPos.x, oldPos.y, desiredPos.z);
    obj->m_collider->UpdatePos(obj->m_pos);

    for (auto& other : objects)
    {
        if (other.get() == obj || !other->m_collider) continue;
        if (obj->m_collider->Intersects(other->m_collider.get()))
        {
            newPos.z = oldPos.z;
            break;
        }
    }

    obj->m_pos = oldPos;

    return newPos;
}

void CollisionSystem::CheckCollisions()
{
    auto& objects = SceneManager::GetObjects();

    for (auto& obj : objects)
    {
        if (!obj->m_collider) continue;

        for (auto& other : objects)
        {
            if (other.get() == obj.get()) continue;
            if (!other->m_collider) continue;

            if (obj->m_collider->Intersects(other->m_collider.get()))
            {
                obj->OnCollision(other.get());
            }
        }
    }
}
