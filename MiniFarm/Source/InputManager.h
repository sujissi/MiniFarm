#pragma once

class InputManager {
public:
	// 입력 매니저 초기화
    static void Init();
	// 키 다운 처리 함수
    static void KeyDown(unsigned char key, int x, int y);
	// 키 업 처리 함수
    static void KeyUp(unsigned char key, int x, int y);
	// 키가 눌려있는지 확인하는 함수
    static bool IsKeyDown(unsigned char key);

private:
	// 키 상태 배열
    static std::array<bool, 256> s_keys;
};