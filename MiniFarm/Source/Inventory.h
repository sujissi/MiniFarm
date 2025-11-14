#pragma once
#include "Types.h"

class Inventory
{
public:
    void AddItem(ItemID id, int count = 1);
    bool UseItem(ItemID id, int count = 1);
    bool HasItem(ItemID id) const;

    void AddMoney(int amount);
    bool SpendMoney(int amount);
    int GetMoney() const { return m_money; }
private:
	std::unordered_map<ItemID, int> m_items;
	int m_money = 0;
};
