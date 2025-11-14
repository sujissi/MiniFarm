#pragma once

class InputManager {
public:
    static void Init();
    static void KeyDown(unsigned char key, int x, int y);
    static void KeyUp(unsigned char key, int x, int y);
    static bool IsKeyDown(unsigned char key);

    static void MouseButton(int button, int state, int x, int y);
    static void MouseMove(int x, int y);
    static int GetDeltaX();
    static int GetDeltaY();
    static void ResetDelta();
private:
    static std::array<bool, 256> s_keys;

    static int s_deltaX;
    static int s_deltaY;

    static int  s_centerX;
    static int  s_centerY;
    static bool s_warping;
    static bool s_rightDown;
};