#include "PCH.h"
#include "SceneManager.h"
#include "Shader.h"

std::vector<std::shared_ptr<GameObject>> SceneManager::s_objects;
Camera SceneManager::s_camera;

void SceneManager::Init()
{
    s_objects.clear();
    s_camera.Init();
}

void SceneManager::AddObject(std::shared_ptr<GameObject> obj)
{
    s_objects.push_back(obj);
}

void SceneManager::Update(float dt)
{
    for (auto& obj : s_objects)
    {
        obj->Update(dt);
    }
}

void SceneManager::Draw()
{
    Shader::Use();
    Shader::SetView(s_camera.GetView());
    Shader::SetProj(s_camera.GetProj((float)WINDOW_W / WINDOW_H));

    for (auto& obj : s_objects)
        obj->Draw();
}