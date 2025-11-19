#include "PCH.h"
#include "SceneManager.h"
#include "Shader.h"
#include "Player.h"
#include "Terrarian.h"
#include "Collider.h"

std::vector<std::shared_ptr<GameObject>> SceneManager::s_objects;
Camera SceneManager::s_camera;

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

void SceneManager::CollisionCheck()
{
    for (int i = 0; i < s_objects.size(); i++)
    {
        for (int j = i + 1; j < s_objects.size(); j++)
        {
            auto a = s_objects[i];
            auto b = s_objects[j];

            if (!a->m_collider || !b->m_collider)
                continue;

            if (a->m_collider->Intersects(b->m_collider.get()))
            {
                a->OnCollision(b.get());
                b->OnCollision(a.get());
            }
        }
    }
}
