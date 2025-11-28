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

protected:
    Camera m_camera;
    Shader m_shader;
    std::vector<std::shared_ptr<GameObject>> m_objects;
};
