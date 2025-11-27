#pragma once
#include <rapidjson/document.h>

class ObjectLoader
{
public:
    static void LoadStaticObjects(const std::string& path);
    static void LoadInteractableObjects(const std::string& path);

private:
    static  bool LoadJson(const std::string& path, rapidjson::Document& doc);
   
    static glm::vec3 ReadVec3(const rapidjson::Value& v);
    static void FlipCoord(glm::vec3& pos, glm::vec3& rot);
};