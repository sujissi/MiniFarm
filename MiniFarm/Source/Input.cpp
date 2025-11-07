#include "PCH.h"
#include "Input.h"

std::unordered_map<unsigned char, bool> Input::s_keys;
bool Input::s_mouseDown = false;

void Input::Init()
{
    s_keys.clear();
    s_mouseDown = false;
}

void Input::KeyDown(unsigned char key)
{
    s_keys[key] = true;
}

void Input::KeyUp(unsigned char key)
{
    s_keys[key] = false;
}

bool Input::IsKeyDown(unsigned char key)
{
    auto it = s_keys.find(key);
    return (it != s_keys.end() && it->second);
}

void Input::MouseDown(int button, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        s_mouseDown = true;
}

void Input::MouseUp(int button, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        s_mouseDown = false;
}

bool Input::IsMouseDown()
{
    return s_mouseDown;
}
