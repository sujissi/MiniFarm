#include "PCH.h"
#include "Shop.h"
#include "Player.h"
#include "InputManager.h"

void Shop::OnInteract(Player* player)
{
    InputManager::SetUIMode(true);
	player->SetShopping(true);
}

void Shop::Buy(Player* player)
{
    if (m_cropType == EItemID::Carrot)
        player->BuySeed(EItemID::SeedCarrot, 1);
    else if (m_cropType == EItemID::Cabbage)
        player->BuySeed(EItemID::SeedCabbage, 1);
}

void Shop::Sell(Player* player)
{
    player->SellCrop(m_cropType, 1);
}