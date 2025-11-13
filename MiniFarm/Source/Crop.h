#pragma once
#include "GameObject.h"

// 작물 ID 열거형 선언
enum class ECropID;
class Crop : public GameObject
{
private:
	ECropID m_id; // 작물 ID
	int   m_level = 0; // 작물 레벨
	float m_time = 0.f; // 경과 시간
	float m_water = 0.f; // 물 양

public:
	Crop(ECropID id); // 작물 생성자 (작물 ID)
	// 작물 업데이트 함수
    void Update(int dt) override;
	// 물 추가 함수
    void AddWater(float amount);
};