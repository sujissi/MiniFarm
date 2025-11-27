#include "PCH.h"
#include "ObjectLoader.h"
#include "SceneManager.h"
#include "ObjectFactory.h"
#include "DataTable.h"
#include "GameObject.h"

bool ObjectLoader::LoadJson(const std::string& path, rapidjson::Document& doc)
{
    std::string json = LoadFile(path);
    if (json.empty()) return false;

    doc.Parse(json.c_str());
    if (!doc.IsObject() || !doc.HasMember("objects"))
        return false;

    return true;
}

glm::vec3 ObjectLoader::ReadVec3(const rapidjson::Value& v)
{
    return glm::vec3(v[0].GetFloat(), v[1].GetFloat(), v[2].GetFloat());
}

void ObjectLoader::FlipCoord(glm::vec3& pos, glm::vec3& rot)
{
    pos.x = -pos.x;
    rot.y = -rot.y;
}

void ObjectLoader::LoadStaticObjects(const std::string& path)
{
    rapidjson::Document doc;
    if (!LoadJson(path, doc)) return;

    auto arr = doc["objects"].GetArray();
    for (auto& obj : arr)
    {
        std::string type = obj["type"].GetString();
        glm::vec3 pos = ReadVec3(obj["pos"]);
        glm::vec3 rot = ReadVec3(obj["rot"]);
        glm::vec3 scale(1.0f);

        FlipCoord(pos, rot);

        auto info = DataTable::GetObjectInfo(type);
        if (!info) continue;

        auto inst = ObjectFactory::Create(type, pos, rot, scale, info);

        inst->m_name = type;
        SceneManager::AddObject(inst);
        inst->Init();
    }
}

void ObjectLoader::LoadInteractableObjects(const std::string& path)
{
    rapidjson::Document doc;
    if (!LoadJson(path, doc)) return;

    auto arr = doc["objects"].GetArray();
    for (auto& obj : arr)
    {
        std::string type = obj["type"].GetString();
        glm::vec3 pos = ReadVec3(obj["pos"]);
        glm::vec3 rot = ReadVec3(obj["rot"]);
        glm::vec3 scale = ReadVec3(obj["scale"]);

        FlipCoord(pos, rot);

        auto info = DataTable::GetObjectInfo(type);
        if (!info) continue;

        auto inst = ObjectFactory::Create(type, pos, rot, scale, info);

        inst->m_name = type;
        SceneManager::AddObject(inst);
        inst->Init();
    }
}

