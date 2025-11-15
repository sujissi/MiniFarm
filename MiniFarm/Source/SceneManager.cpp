#include "PCH.h"
#include "SceneManager.h"
#include "Shader.h"
#include "Player.h"
#include "House.h"

std::vector<std::shared_ptr<GameObject>> SceneManager::s_objects;
Camera SceneManager::s_camera;

void SceneManager::Init()
{
    s_objects.clear();
    s_camera.Init();
    
    AddObject(std::make_shared<Player>());
    AddObject(std::make_shared<House>());
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
        obj->Draw();

    glutSwapBuffers();
}

void SceneManager::Reshape(int w, int h)
{
    glViewport(0, 0, w, h);

}
