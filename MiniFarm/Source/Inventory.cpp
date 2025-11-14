#include "PCH.h"
#include "Inventory.h"

void Inventory::AddItem(EItemID id, int count)
{
	items[id] += count;
}

bool Inventory::UseItem(EItemID id)
{
	if (items.find(id) == items.end())
		return false;

	items[id]--;
	return true;
}
