#pragma once

class Camera {
public:
	// 카메라 생성자
    Camera();
	// 카메라 초기화 함수
    void Init();
	// 카메라 앞뒤 이동 함수
    //void MoveForward(float amount);
	// 카메라 좌우 이동 함수
    //void MoveRight(float amount);
	// 카메라 좌우 회전 함수
    //void RotateYaw(float deg);
	// 뷰 행렬 반환 함수
    glm::mat4 GetView() const;
	// 투영 행렬 반환 함수
    glm::mat4 GetProj(float aspect) const;

public:
    glm::vec3 eye; // 카메라 위치
	glm::vec3 at; // 카메라 주시점
	glm::vec3 up; // 카메라 업 벡터
};
