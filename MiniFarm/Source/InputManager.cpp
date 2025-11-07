#include "PCH.h"
#include "InputManager.h"

std::array<bool, 256> InputManager::s_keys;

void InputManager::Init()
{
    s_keys.fill(false);
    LOG_D("Input Initialized");
}

void InputManager::KeyDown(unsigned char key, int x, int y)
{
    s_keys[key] = true;
    LOG_D("KeyDown: %c (%d)", key, key);
}

void InputManager::KeyUp(unsigned char key, int x, int y)
{
    s_keys[key] = false;
    LOG_D("KeyUp: %c (%d)", key, key);
}

bool InputManager::IsKeyDown(unsigned char key)
{
    return s_keys[key];
}
