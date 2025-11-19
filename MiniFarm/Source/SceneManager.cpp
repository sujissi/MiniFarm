#include "PCH.h"
#include "SceneManager.h"
#include "Shader.h"
#include "Player.h"
#include "Terrarian.h"
#include "Collider.h"

std::vector<std::shared_ptr<GameObject>> SceneManager::s_objects;
Camera SceneManager::s_camera;
GameObject* SceneManager::s_selected = nullptr;

void SceneManager::Init()
{
    s_objects.clear();
    s_camera.Init();
    
    AddObject(std::make_shared<Player>());
    AddObject(std::make_shared<House>(glm::vec3(-10.0f, 0.0f, -10.f)));
    AddObject(std::make_shared<House>(glm::vec3(0.0f, 0.0f, -10.f)));
    AddObject(std::make_shared<House>(glm::vec3(10.0f, 0.0f, -10.f)));
    AddObject(std::make_shared<Fance>(glm::vec3(-10.0f, 0.0f, 10.f)));
    AddObject(std::make_shared<Fance>(glm::vec3(10.0f, 0.0f, 10.f)));

    for (auto& obj : s_objects)
    {
        obj->Init();
    }
}

void SceneManager::AddObject(std::shared_ptr<GameObject> obj)
{
    s_objects.push_back(obj);
}

void SceneManager::Update(int time)
{
    for (auto& obj : s_objects)
    {
        obj->Update(time);
    }
    glutPostRedisplay();
    glutTimerFunc(FRAME_TIME_MS, SceneManager::Update, 0);
}

void DrawGround()
{
    glColor3f(0.6f, 0.6f, 0.6f);

    glBegin(GL_LINES);

    for (int i = -50; i <= 50; i++)
    {
        glVertex3f((float)i, 0.f, -50.f);
        glVertex3f((float)i, 0.f, 50.f);

        glVertex3f(-50.f, 0.f, (float)i);
        glVertex3f(50.f, 0.f, (float)i);
    }

    glEnd();
}

void SceneManager::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader::Use();
    Shader::SetView(s_camera.GetView());
    Shader::SetProj(s_camera.GetProj((float)WINDOW_W / WINDOW_H));
    
    Shader::SetModel(glm::mat4(1.0f));
    DrawGround();

    for (auto& obj : s_objects)
    {
		obj->DebugDraw();
        obj->Draw();
    }

    glutSwapBuffers();
}

void SceneManager::Reshape(int w, int h)
{
    glViewport(0, 0, w, h);

}

glm::vec3 SceneManager::TryMove(GameObject* obj, const glm::vec3& desiredPos)
{
    if (!obj->m_collider)
        return desiredPos;

    glm::vec3 oldPos = obj->m_pos;
    glm::vec3 newPos = desiredPos;

    obj->m_pos = glm::vec3(desiredPos.x, oldPos.y, oldPos.z);
    obj->m_collider->UpdatePos(obj->m_pos);

    for (auto& other : s_objects)
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

    for (auto& other : s_objects)
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

static Ray ScreenPointToRay(int x, int y)
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

static bool RayGround(const Ray& ray, glm::vec3& hit)
{
    glm::vec3 planeNormal(0, 1, 0);
    float denom = glm::dot(ray.dir, planeNormal);

    if (fabs(denom) < 1e-6f)
        return false;

    float t = -ray.origin.y / denom;
    if (t < 0) return false;

    hit = ray.origin + ray.dir * t;
    return true;
}

void SceneManager::OnMouseClick(int x, int y)
{
    Ray ray = ScreenPointToRay(x, y);

    auto clickedObj = PickObject(ray);

    if (clickedObj && dynamic_cast<Player*>(clickedObj))
        return;

    if (clickedObj)
    {
        s_selected = clickedObj;
        LOG_D("Selected %s", clickedObj->m_name.c_str());
        return;
    }

    s_selected = nullptr;
    LOG_D("Selection cleared");
}

GameObject* SceneManager::PickObject(const Ray& ray)
{
    GameObject* picked = nullptr;
    float nearestT = FLT_MAX;

    for (auto& obj : s_objects)
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

void SceneManager::CollisionCheck()
{
    for (auto& obj : s_objects)
    {
        if (!obj->m_collider) continue;

        for (auto& other : s_objects)
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
