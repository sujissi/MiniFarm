#include "PCH.h"
#include "InputManager.h"

std::array<bool, 256> InputManager::s_keys;

int  InputManager::s_deltaX = 0;
int  InputManager::s_deltaY = 0;
int  InputManager::s_centerX = 0;
int  InputManager::s_centerY = 0;
bool InputManager::s_warping = false;
bool InputManager::s_uiMode = false;

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

	switch (key)
	{
		case 't': SetUIMode(false); break; //temp
		case 'q': exit(0);
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (s_uiMode)
		{
			// TODO:
			// UIManager::OnClick(x, y);
			return;
		}

		s_uiMode = !s_uiMode;
		SetUIMode(s_uiMode);
		return;
	}
}

void InputManager::MouseMove(int x, int y)
{
	if (s_uiMode)
		return;

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

void InputManager::ResetDelta()
{
	if (s_uiMode)
	{
		s_deltaX = 0;
		s_deltaY = 0;
		return;
	}
}

void InputManager::SetUIMode(bool enable)
{
	LOG_D("UI Mode %s", (enable) ? "On" : "Off");
	s_uiMode = enable;

	if (enable)
	{
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
	else
	{
		glutSetCursor(GLUT_CURSOR_NONE);
		s_warping = true;
		glutWarpPointer(s_centerX, s_centerY);
	}
}
