#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player();
    virtual void Update(int time);
private:
    float m_speed;
};
