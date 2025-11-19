#pragma once

struct Ray
{
    glm::vec3 origin;
    glm::vec3 dir;
};

class GameObject;
class PickingSystem
{
public:
    static Ray ScreenPointToRay(int x, int y);
    static GameObject* PickObject(int x, int y);
};
