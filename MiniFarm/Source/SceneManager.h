#pragma once
#include "GameObject.h"
#include "Camera.h"

class SceneManager
{
public:
	// 씬 매니저 초기화 함수
    static void Init();
    // 오브젝트 추가 함수
    static void AddObject(std::shared_ptr<GameObject> obj);
	// 오브젝트 업데이트 함수
    static void Update(int time);
	// 오브젝트 그리기 함수
    static void Draw();
    // 다시 그리기 함수
    static void Reshape(int w, int h);
	// 카메라 반환 함수
    static Camera& GetCamera() { return s_camera; }
private:
	// 게임 오브젝트 리스트
    static std::vector<std::shared_ptr<GameObject>> s_objects;
	// 카메라 객체
    static Camera s_camera;
};
