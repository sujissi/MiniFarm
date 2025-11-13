#include "PCH.h"
#include "InputManager.h"

// 키 상태 배열
std::array<bool, 256> InputManager::s_keys;

// 입력 매니저 초기화
void InputManager::Init()
{
    LOG("Input Init");
    s_keys.fill(false);
}
// 키 다운 처리 함수
void InputManager::KeyDown(unsigned char key, int x, int y)
{
    s_keys[key] = true;
    LOG_D("KeyDown: %c (%d)", key, key);
}
// 키 업 처리 함수
void InputManager::KeyUp(unsigned char key, int x, int y)
{
    s_keys[key] = false;
    LOG_D("KeyUp: %c (%d)", key, key);
}
// 키가 눌려있는지 확인하는 함수
bool InputManager::IsKeyDown(unsigned char key)
{
    return s_keys[key];
}
