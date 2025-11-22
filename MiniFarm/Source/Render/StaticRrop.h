#pragma once
#include "GameObject.h"


class StaticProp : public GameObject
{
public:
    std::string modelPath;

    StaticProp(const glm::vec3& pos,
        const glm::vec3& rot,
        const glm::vec3& scale,
        const std::string& model)
        : GameObject(pos, rot, scale), modelPath(model)
    {
    }

    void Init() override
    {
        m_model = std::make_shared<Model>(modelPath, "Models/Farm_texture.png");
    }
};
