#include "PCH.h"
#include "Inventory.h"

void Inventory::AddItem(ItemID id, int count)
{
	m_items[id] += count;
}

bool Inventory::UseItem(ItemID id, int count)
{
	if (!HasItem(id))
		return false;

	m_items[id] -= count;
	return true;
}

bool Inventory::HasItem(ItemID id) const
{
	return m_items.find(id) != m_items.end() && m_items.at(id) > 0;
}

void Inventory::AddMoney(int amount)
{
	m_money += amount;
}

bool Inventory::SpendMoney(int amount)
{
	if (m_money < amount) return false;
	m_money -= amount;
	return true;
}
