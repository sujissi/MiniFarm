#pragma once
class Scene
{
public:
    virtual void Init() = 0;
    virtual void Update(int dt) = 0;
    virtual void Draw() = 0;
    virtual void OnKey(unsigned char key) {}
    virtual ~Scene() {}
};
