#pragma once
#include "GameObject.h"
#include "SceneManager.h"
#include "InputManager.h"

class Player : public GameObject
{
public:
    Player()
    {
        m_model = std::make_shared<Model>("Models/cube.obj");
        m_pos = { 0.f, 0.f, 0.f };
        m_rot = { 0.f, 0.f, 0.f };
        m_scale = { 1.f, 1.f, 1.f };
    }

    void Update(int time) override
    {
        auto& cam = SceneManager::GetCamera();

        if (InputManager::IsKeyDown('w')) cam.MoveForward(0.05f);
        if (InputManager::IsKeyDown('s')) cam.MoveForward(-0.05f);
        if (InputManager::IsKeyDown('a')) cam.RotateYaw(-1.5f);
        if (InputManager::IsKeyDown('d')) cam.RotateYaw(1.5f);
    }
    
};
