#include "PCH.h"
#include "Inventory.h"
#include "UIRenderer.h"
#include "TextRenderer.h"

Inventory::Inventory()
{
	//for test
	AddItem(EItemID::Carrot, 5);
	m_money = 1000;
}

void Inventory::AddItem(EItemID id, int count)
{
	m_items[id] += count;
}

bool Inventory::UseItem(EItemID id, int count)
{
	if (!HasItem(id))
		return false;

	m_items[id] -= count;
	return true;
}

bool Inventory::HasItem(EItemID id) const
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

void Inventory::DrawUI() const
{
	UIRenderer::Draw(TextureLoader::Load("Assets/ui_inventory.png"), { 0.01f,0.01f }, 0.45f);
	UIRenderer::Draw(TextureLoader::Load("Assets/ui_goldbar.png"), { 0.01f,0.9f }, 0.25f);

	std::string moneyStr = std::to_string(m_money);
	TextRenderer::DrawLeft(moneyStr, 50, WINDOW_H - 50, 2, { 0,0,0 });

}
