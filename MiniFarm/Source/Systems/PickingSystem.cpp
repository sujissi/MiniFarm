#include "PCH.h"
#include "PickingSystem.h"
#include "SceneManager.h"
#include "Collider.h"


Ray PickingSystem::ScreenPointToRay(int x, int y)
{
    float nx = (2.0f * x) / WINDOW_W - 1.0f;
    float ny = 1.0f - (2.0f * y) / WINDOW_H;

    glm::vec4 startClip(nx, ny, -1, 1);
    glm::vec4 endClip(nx, ny, 1, 1);

    float aspect = (float)WINDOW_W / (float)WINDOW_H;
    glm::mat4 view = SceneManager::GetCamera().GetView();
    glm::mat4 proj = SceneManager::GetCamera().GetProj(aspect);

    glm::mat4 invVP = glm::inverse(proj * view);

    glm::vec4 startWorld = invVP * startClip;
    glm::vec4 endWorld = invVP * endClip;

    startWorld /= startWorld.w;
    endWorld /= endWorld.w;

    Ray ray;
    ray.origin = glm::vec3(startWorld);
    ray.dir = glm::normalize(glm::vec3(endWorld - startWorld));
    return ray;
}

GameObject* PickingSystem::PickObject(int x, int y)
{
    Ray ray = ScreenPointToRay(x, y);

    GameObject* picked = nullptr;
    float nearestT = FLT_MAX;

    auto& objects = SceneManager::GetObjects();
    for (auto& obj : objects)
    {
        if (!obj->m_collider) continue;

        float t;
        glm::vec3 hit;

        if (obj->m_collider->Raycast(ray.origin, ray.dir, t, hit))
        {
            if (t < nearestT)
            {
                nearestT = t;
                picked = obj.get();
            }
        }
    }

    return picked;
}
