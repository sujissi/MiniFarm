#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
    // 플레이어 생성자
    Player();
    // 플레이어 업데이트 함수
    virtual void Update(int time);
private:
    // 이동 속도
    float speed;
};