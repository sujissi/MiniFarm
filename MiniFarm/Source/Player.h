#pragma once
#include "GameObject.h"
#include "Inventory.h"
#include "Types.h"

class Player : public GameObject
{
public:
    Player();
    virtual void Update(int time);

private:
	void HandleRotate();
	void HandleMove();
	void HandleInteractTest(); //for test
	
	void UseTool(ItemID toolID);
	void BuySeed(ItemID seedID, int count);
	void SellCrop(ItemID cropID, int count);
private:
    float m_speed;
	Inventory m_inventory;
};
