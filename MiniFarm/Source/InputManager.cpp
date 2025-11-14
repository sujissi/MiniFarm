#include "PCH.h"
#include "InputManager.h"

std::array<bool, 256> InputManager::s_keys;

int  InputManager::s_deltaX = 0;
int  InputManager::s_deltaY = 0;
int  InputManager::s_centerX = 0;
int  InputManager::s_centerY = 0;
bool InputManager::s_warping = false; 
bool InputManager::s_rightDown = true;

void InputManager::Init()
{
    LOG("Input Init");
    glutSetCursor(GLUT_CURSOR_NONE);

    s_keys.fill(false);
    s_centerX = WINDOW_W / 2;
    s_centerY = WINDOW_H / 2;

    s_warping = true;
    glutWarpPointer(s_centerX, s_centerY);
}

void InputManager::KeyDown(unsigned char key, int x, int y)
{
    s_keys[key] = true;
    
    if (key == 'q') 
    {
        exit(0);
    }
}

void InputManager::KeyUp(unsigned char key, int x, int y)
{
    s_keys[key] = false;
}

bool InputManager::IsKeyDown(unsigned char key)
{
    return s_keys[key];
}

void InputManager::MouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            s_rightDown = true;
        }
        else if (state == GLUT_UP)
        {
            s_rightDown = false;
        }
    }
}
void InputManager::MouseMove(int x, int y)
{
    if (s_warping)
    {
        s_warping = false;
        return;
    }

    s_deltaX = x - s_centerX;
    s_deltaY = y - s_centerY;

    s_warping = true;
    glutWarpPointer(s_centerX, s_centerY);
}

int InputManager::GetDeltaX() { return s_deltaX; }
int InputManager::GetDeltaY() { return s_deltaY; }

void InputManager::ResetDelta()
{
    s_deltaX = 0;
    s_deltaY = 0;
}
