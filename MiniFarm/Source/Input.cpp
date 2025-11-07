#include "PCH.h"
#include "Input.h"

std::array<bool, 256> Input::s_keys;

void Input::Init()
{
    s_keys.fill(false);
    LOG_D("Input Initialized");
}

void Input::KeyDown(unsigned char key, int x, int y)
{
    s_keys[key] = true;
    LOG_D("KeyDown: %c (%d)", key, key);
}

void Input::KeyUp(unsigned char key, int x, int y)
{
    s_keys[key] = false;
    LOG_D("KeyUp: %c (%d)", key, key);
}

bool Input::IsKeyDown(unsigned char key)
{
    return s_keys[key];
}
