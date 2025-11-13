#pragma once
#include "Model.h"

class GameObject
{
public:
	// 게임 오브젝트 모델 (shared pointer - 스마트 포인터로 모델 관리)
    std::shared_ptr<Model> m_model;
    // 오브젝트 위치
    glm::vec3 m_pos;
    // 오브젝트 방향
	glm::vec3 m_rot; // (x각도, y각도, z각도)
    // 오브젝트 크기
    glm::vec3 m_scale;
public:
    // 게임 오브젝트 소멸자
    virtual ~GameObject() = default;
    // 개임 오브젝트 업데이트 함수
    virtual void Update(int time) {}
	// 게임 오브젝트 그리기 함수
    virtual void Draw();
};