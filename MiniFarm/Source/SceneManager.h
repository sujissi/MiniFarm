#pragma once
#include "GameObject.h"
#include "Camera.h"

class SceneManager
{
public:
    static void Init();
    static void AddObject(std::shared_ptr<GameObject> obj);

    static void Update(int time);
    static void Draw();
    static void Reshape(int w, int h);

    static Camera& GetCamera() { return s_camera; }
private:
    static std::vector<std::shared_ptr<GameObject>> s_objects;
    static Camera s_camera;
};
