#include "PCH.h"
#include "Boat.h"
#include "Player.h"
#include "InputManager.h"

void Boat::OnInteract(Player* player)
{
	static constexpr int escapeCost = 100;

	int money = player->GetInventory().GetMoney();
	bool canEscape = money >= escapeCost;

	auto msg = canEscape ? "Are you sure?\nYes[Y]\nNo[N]"
		: std::format("Not enough money\nto escape!\n need {}G.\n\nOK[space]", escapeCost - money);
	
	InputManager::SetUIMode(true);
	player->SetSysMsg(msg);
	player->SetEscaping(true);
	player->SetCanEscape(canEscape);
}
