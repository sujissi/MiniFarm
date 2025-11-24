#include "PCH.H"
#include "Player.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "DataTable.h"
#include "BoxCollider.h"
#include "CollisionSystem.h"
#include "IInteractable.h"
#include "Text.h"

Player::Player()
{
	m_model = std::make_shared<Model>("Models/player");
	m_pos = { 0.f, 6.2f, 0.f };
	m_rot = { 0.f, 0.f, 0.f };
	m_scale = { 1.f, 1.f, 1.f };
    m_speed = 0.3f;

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

    float rotSpeed = 0.2f;
    cam.AddYaw(InputManager::GetDeltaX() * rotSpeed);
    cam.AddPitch(-InputManager::GetDeltaY() * rotSpeed);

    m_rot.y = cam.GetFlatYaw();

    InputManager::ResetDelta();
}

void Player::HandleMove()
{
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
        LOG("상호작용");
        m_FocusedInteractable->OnInteract(this);
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
    }
}


void Player::UseTool(ItemID toolID)
{
	auto tool = static_cast<EToolID>(toolID);

    //TODO: 각 애니메이션 다르게?
    switch (tool)
    {
	case EToolID::Hoe:
        break;
	case EToolID::WateringCan:
		break;
	case EToolID::Sickle:
		break;
    case EToolID::SeedCarrot:
    case EToolID::SeedCabbage:
		break;
    }

    LOG_D("도구 사용");
}

void Player::BuySeed(ItemID seedID, int count)
{
    auto seed = static_cast<EToolID>(seedID);
    const CropData* data = nullptr;
    switch (seed)
    {
    case EToolID::SeedCarrot:
        data = DataTable::GetCrop(ECropID::Carrot);
        break;
    case EToolID::SeedCabbage:
        data = DataTable::GetCrop(ECropID::Cabbage);
        break;
    default:
        return;
    }
    int totalPrice = data->seedPrice * count;
    if (m_inventory.SpendMoney(totalPrice))
    {
        m_inventory.AddItem(seedID, count);
        LOG_D("%s를 %d개 구매 (-%d원) ", data->name.c_str(), count, totalPrice);
	}
    else
    {
        LOG_D("금액 부족");
    }
}

void Player::SellCrop(ItemID cropID, int count)
{
    auto crop = static_cast<ECropID>(cropID);
    const CropData* data = nullptr;
    switch (crop)
    {
    case ECropID::Carrot:
        data = DataTable::GetCrop(ECropID::Carrot);
        break;
    case ECropID::Cabbage:
        data = DataTable::GetCrop(ECropID::Cabbage);
        break;
    default:
        return;
    }

    if(m_inventory.UseItem(cropID, count))
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
