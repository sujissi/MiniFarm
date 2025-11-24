#pragma once
#include "GameObject.h"
#include "Inventory.h"

class IInteractable;
class Player : public GameObject
{
public:
    Player();
    virtual void Update(int time);

private:
	void HandleRotate();
	void HandleMove();
	void HandleInteractInput();
	void TryUpdateInteractTarget();
	IInteractable* m_FocusedInteractable = nullptr;

	void UseTool(ItemID toolID);
	void BuySeed(ItemID seedID, int count);
	void SellCrop(ItemID cropID, int count);
private:
    float m_speed;
	Inventory m_inventory;
};
