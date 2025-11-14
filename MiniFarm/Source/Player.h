#pragma once
#include "GameObject.h"
#include "Inventory.h"

class Player : public GameObject
{
public:
    Player();
    virtual void Update(int time);

private:
    float m_speed;
	Inventory m_inventory;
};
