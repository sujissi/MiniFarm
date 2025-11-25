#pragma once
#include "GameObject.h"
#include "Inventory.h"

class IInteractable;
class Text;
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
	
	void HandleEquipmentInput();
public:
	void BuySeed(EItemID seedID, int count = 1);
	void SellCrop(EItemID cropID, int count = 1);
	void AddItem(EItemID itemID, int count = 1);

	bool HasInteractTarget() { return m_FocusedInteractable != nullptr; }
	EItemID GetEquippedTool() const { return m_equippedTool; }
	void SetEquippedTool(EItemID tool) { m_equippedTool = tool; }
private:
    float m_speed = 0.2f;
	Inventory m_inventory;
	IInteractable* m_FocusedInteractable = nullptr;
	EItemID m_equippedTool = EItemID::Empty;
};
