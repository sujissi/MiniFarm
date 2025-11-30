#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Shader.h"

class Scene
{
public:
    virtual void Init() = 0;
    virtual void Update(int dt) = 0;
    virtual void Draw() = 0;
    virtual ~Scene() {}

    Camera& GetCamera() { return m_camera; }
    Shader& GetMainShader() { return m_shader; }
    std::vector<std::shared_ptr<GameObject>>& GetObjects() { return m_objects; }
    void AddObject(std::shared_ptr<GameObject> obj)
    {
        m_objects.push_back(obj);
    }
    glm::vec3 GetClearColor() const { return m_clearColor; }
    void SetClearColor(const glm::vec3& color) { m_clearColor = color; }

protected:
    Camera m_camera;
    Shader m_shader;
    std::vector<std::shared_ptr<GameObject>> m_objects;
    glm::vec3 m_clearColor = glm::vec3(0.f);
};
