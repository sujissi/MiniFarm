#include "PCH.H"
#include "Player.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "DataTable.h"
#include "BoxCollider.h"
#include "CollisionSystem.h"
#include "IInteractable.h"
#include "Shop.h"

Player::Player()
{
	m_model = std::make_shared<Model>("Models/player");
	m_pos = { 0.f, 6.2f, 0.f };
	m_rot = { 0.f, 0.f, 0.f };
	m_scale = { 1.f, 1.f, 1.f };

	m_collider = std::make_shared<BoxCollider>(
		glm::vec3(-0.5f, 0.0f, -0.5f),
		glm::vec3(0.5f, 2.0f, 0.5f)
	);

	m_alive = true;
	m_name = "player";
}

void Player::Update(int time)
{
	TryUpdateInteractTarget();
	HandleInteractInput();
	HandleEquipmentInput();
	HandleShopDirectInput();
	HandleBoatDirectInput();

	HandleRotate();
	HandleMove();

	GameObject::Update(time);
	InputManager::Update();
}

void Player::HandleRotate()
{
	if (InputManager::IsUIMode())
		return;

	auto& cam = SceneManager::GetCamera();

	float rotSpeed = 0.1f;
	cam.AddYaw(InputManager::GetDeltaX() * rotSpeed);
	cam.AddPitch(-InputManager::GetDeltaY() * rotSpeed);

	m_rot.y = cam.GetFlatYaw();

	InputManager::ResetDelta();
}

void Player::HandleMove()
{
	if (InputManager::IsUIMode())
		return;

	auto& cam = SceneManager::GetCamera();

	glm::vec3 forward = cam.GetForwardFlat();
	glm::vec3 right = cam.GetRightFlat();

	glm::vec3 move(0);

	if (InputManager::IsKeyDown('w')) move += forward;
	if (InputManager::IsKeyDown('s')) move -= forward;
	if (InputManager::IsKeyDown('a')) move -= right;
	if (InputManager::IsKeyDown('d')) move += right;

	if (glm::length(move) > 0)
	{
		glm::vec3 desired = m_pos + glm::normalize(move) * m_speed;
		m_pos = CollisionSystem::TryMove(this, desired);
	}
	cam.FollowTarget(m_pos);
}

void Player::HandleInteractInput()
{
	if (m_FocusedInteractable == nullptr)
		return;

	if (InputManager::IsKeyPressed('e'))
	{
		LOG_D("상호작용");
		m_FocusedInteractable->OnInteract(this);
	}
}

void Player::HandleEquipmentInput()
{
	if (InputManager::IsKeyPressed('1'))
	{
		SetEquippedTool(EItemID::Hoe);
		LOG_D("도구 변경: 괭이");
	}
	else if (InputManager::IsKeyPressed('2'))
	{
		SetEquippedTool(EItemID::WateringCan);
		LOG_D("도구 변경: 물뿌리개");
	}
	else if (InputManager::IsKeyPressed('3'))
	{
		SetEquippedTool(EItemID::Sickle);
		LOG_D("도구 변경: 낫");
	}
	else if (InputManager::IsKeyPressed('4'))
	{
		SetEquippedTool(EItemID::SeedCarrot);
		LOG_D("도구 변경: 당근 씨앗");
	}
	else if (InputManager::IsKeyPressed('5'))
	{
		SetEquippedTool(EItemID::SeedCabbage);
		LOG_D("도구 변경: 양배추 씨앗");
	}
}

void Player::HandleShopDirectInput()
{
	if (!m_CurrentShop || !IsShopping()) return;

	if (InputManager::IsKeyPressed('b'))
	{
		LOG("구매 시도");
		m_CurrentShop->Buy(this);
	}

	if (InputManager::IsKeyPressed('s'))
	{
		LOG("판매 시도");
		m_CurrentShop->Sell(this);
	}

	if (InputManager::IsKeyPressed('x'))
	{
		LOG("상점 이용 종료");
		InputManager::SetUIMode(false);
		SetShopping(false);
	}
}

void Player::HandleBoatDirectInput()
{
	if(!IsEscaping())
		return;

	if (InputManager::IsKeyPressed('y'))
	{
		LOG("탈출 시도");
		if (CanEscape())
		{
			//TODO: 탈출 처리
			LOG("탈출 성공!");
		}
	}
	if (InputManager::IsKeyPressed('n')|| InputManager::IsKeyPressed(' '))
	{
		InputManager::SetUIMode(false);
		SetEscaping(false);
	}
}

void Player::TryUpdateInteractTarget()
{
	m_FocusedInteractable = nullptr;

	const auto& objects = SceneManager::GetObjects();
	glm::vec3 playerPos = m_pos;

	float bestDistance = std::numeric_limits<float>::max();

	for (const auto& obj : objects)
	{
		if (obj.get() == this)
			continue;

		IInteractable* interactable = dynamic_cast<IInteractable*>(obj.get());
		if (!interactable || !interactable->IsInteractable())
			continue;

		float maxDistance = interactable->GetInteractDistance();

		glm::vec3 toObj = obj->m_pos - playerPos;

		float dist = glm::length(toObj);
		if (dist > maxDistance)
			continue;

		if (dist < bestDistance)
		{
			bestDistance = dist;
			m_FocusedInteractable = interactable;
		}

		if (Shop* shop = dynamic_cast<Shop*>(obj.get()))
		{
			m_CurrentShop = shop;
		}
	}
}

void Player::BuySeed(EItemID seedID, int count)
{
	const CropData* data = nullptr;
	switch (seedID)
	{
	case EItemID::SeedCarrot:
		data = DataTable::GetCrop(EItemID::Carrot);
		break;
	case EItemID::SeedCabbage:
		data = DataTable::GetCrop(EItemID::Cabbage);
		break;
	default:
		return;
	}
	int totalPrice = data->seedPrice * count;
	if (m_inventory.SpendMoney(totalPrice))
	{
		AddItem(seedID, count);
		LOG_D("%s를 %d개 구매 (-%d원) ", data->name.c_str(), count, totalPrice);
	}
	else
	{
		LOG_D("금액 부족");
	}
}

void Player::SellCrop(EItemID cropID, int count)
{
	const CropData* data = nullptr;
	switch (cropID)
	{
	case EItemID::Carrot:
		data = DataTable::GetCrop(EItemID::Carrot);
		break;
	case EItemID::Cabbage:
		data = DataTable::GetCrop(EItemID::Cabbage);
		break;
	default:
		return;
	}

	if (m_inventory.UseItem(cropID, count))
	{
		int totalPrice = data->sellPrice * count;
		m_inventory.AddMoney(totalPrice);
		LOG_D("%s를 %d개 판매 (+%d원) ", data->name.c_str(), count, totalPrice);
	}
	else
	{
		LOG_D("판매할 %s 없음", data->name.c_str());
	}
}

void Player::AddItem(EItemID itemID, int count)
{
	m_inventory.AddItem(itemID, count);
}