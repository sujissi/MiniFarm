#include "PCH.h"
#include "SceneManager.h"
#include "Shader.h"
#include "Player.h"
#include "PickingSystem.h"
#include <rapidjson/document.h>
#include "DataTable.h"
#include "StaticRrop.h"

std::vector<std::shared_ptr<GameObject>> SceneManager::s_objects;
Camera SceneManager::s_camera;
GameObject* SceneManager::s_selected = nullptr;

void SceneManager::Init()
{
    s_objects.clear();
    s_camera.Init();
	DataTable::Init();
    AddObject(std::make_shared<Player>());
    LoadMap("Data/ObjectPosition.json");
}

void SceneManager::AddObject(std::shared_ptr<GameObject> obj)
{
    s_objects.push_back(obj);
}

void SceneManager::LoadMap(const std::string& path)
{
    std::string json = LoadFile(path);

    if (json.empty()) {
		LOG_E("Failed to load map file: %s", path.c_str());
        return;
    }

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    if (!doc.IsObject() || !doc.HasMember("objects")) {
		LOG_E("Invalid map file: %s", path.c_str());
        return;
    }

    const auto& arr = doc["objects"].GetArray();

    auto readVec3 = [&](const rapidjson::Value& v)
        {
            return glm::vec3(
                v[0].GetFloat(),
                v[1].GetFloat(),
                v[2].GetFloat()
            );
        };

    for (auto& obj : arr)
    {
        std::string type = obj["type"].GetString();
        glm::vec3 pos = readVec3(obj["pos"]);
        glm::vec3 rot = readVec3(obj["rot"]);
        glm::vec3 scale = readVec3(obj["scale"]);

        std::string model = DataTable::GetObjectModel(type);
        auto inst = std::make_shared<StaticProp>(pos, rot, scale, model);
        if (inst)
        {
            AddObject(inst);
            inst->Init();
        }
        else
            LOG_E("Unknown object type: %s", type.c_str());
    }
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

void SceneManager::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader::Use();
    Shader::SetView(s_camera.GetView());
    Shader::SetProj(s_camera.GetProj((float)WINDOW_W / WINDOW_H));
    
    Shader::SetLightPos(glm::vec3(10.f, 15.f, 10.f));
    Shader::SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
    Shader::SetViewPos(s_camera.eye);

    Shader::SetModel(glm::mat4(1.0f));

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