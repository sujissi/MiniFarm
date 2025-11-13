#pragma once

class InputManager {
public:
    static void Init();
    static void KeyDown(unsigned char key, int x, int y);
    static void KeyUp(unsigned char key, int x, int y);
    static bool IsKeyDown(unsigned char key);

private:
    static std::array<bool, 256> s_keys;
};