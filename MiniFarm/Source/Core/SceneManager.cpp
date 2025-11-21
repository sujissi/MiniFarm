#include "PCH.h"
#include "SceneManager.h"
#include "Shader.h"
#include "Player.h"
#include "Landform.h"
#include "PickingSystem.h"

std::vector<std::shared_ptr<GameObject>> SceneManager::s_objects;
Camera SceneManager::s_camera;
GameObject* SceneManager::s_selected = nullptr;

void SceneManager::Init()
{
    s_objects.clear();
    s_camera.Init();
    
    AddObject(std::make_shared<Player>());
    AddObject(std::make_shared<House>(glm::vec3(-10.f, 0.f, -10.f)));
    AddObject(std::make_shared<House>(glm::vec3(0.f, 0.f, -10.f)));
    AddObject(std::make_shared<Fance>(glm::vec3(-10.f, 0.f, 10.f)));
    AddObject(std::make_shared<Fance>(glm::vec3(10.f, 0.f, 10.f)));
	AddObject(std::make_shared<Ground>(glm::vec3(0.f, -2.2f, 0.f)));
	AddObject(std::make_shared<Tree>(glm::vec3(0.f, -2.2f, 0.f)));
	AddObject(std::make_shared<Boat>(glm::vec3(0.f, -2.2f, 0.f)));

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

void SceneManager::OnMouseClick(int x, int y)
{
    auto clickedObj = PickingSystem::PickObject(x, y);

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