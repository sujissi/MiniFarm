#pragma once
#include "GameObject.h"
#include "Camera.h"

struct Ray
{
    glm::vec3 origin;
    glm::vec3 dir;
};

class SceneManager
{
public:
    static void Init();
    static void AddObject(std::shared_ptr<GameObject> obj);

    static void Update(int time);
    static void Draw();
    static void Reshape(int w, int h);

    static glm::vec3 TryMove(GameObject* obj, const glm::vec3& desiredPos);
    static void OnMouseClick(int x, int y);
    static GameObject* PickObject(const Ray& ray);

    static void CollisionCheck();
    static Camera& GetCamera() { return s_camera; }
private:
    static std::vector<std::shared_ptr<GameObject>> s_objects;
    static Camera s_camera;

    static GameObject* s_selected;
};
