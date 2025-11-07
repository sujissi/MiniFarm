#pragma once

class Input
{
public:
    static void Init();

    static void KeyDown(unsigned char key);
    static void KeyUp(unsigned char key);

    static bool IsKeyDown(unsigned char key);

    static void MouseDown(int button, int x, int y);
    static void MouseUp(int button, int x, int y);

    static bool IsMouseDown();

private:
    static std::unordered_map<unsigned char, bool> s_keys;
    static bool s_mouseDown;
};
