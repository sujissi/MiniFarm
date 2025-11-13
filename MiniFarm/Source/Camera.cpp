#include "PCH.h"
#include "Camera.h"

// 카메라 생성자
Camera::Camera()
{
    // 초기화 함수 호출
    Init();
}

// 카메라 초기화 함수
void Camera::Init()
{
	// 카메라 위치, 주시점, 업 벡터 설정
    eye = { 0.0f, 3.0f, 10.0f };
    at = { 0.0f, 0.0f, 0.0f };
    up = { 0.0f, 1.0f, 0.0f };
}

// 카메라 앞뒤 이동 함수
//void Camera::MoveForward(float amount)
//{
//    LOG("");
//    glm::vec3 dir = glm::normalize(at - eye);
//    eye += dir * amount;
//    at += dir * amount;
//	  eye.z += amount;
//}

// 카메라 좌우 이동 함수
//void Camera::MoveRight(float amount)
//{
//    LOG("");
//    glm::vec3 dir = glm::normalize(at - eye);
//    glm::vec3 right = glm::normalize(glm::cross(dir, up));
//    eye += right * amount;
//    at += right * amount;
//	  eye.x += amount;
//}

// 카메라 좌우 회전 함수
//void Camera::RotateYaw(float deg)
//{
//    LOG("");
//    float rad = glm::radians(deg);
//    glm::vec3 dir = at - eye;
//    float nx = dir.x * cos(rad) - dir.z * sin(rad);
//    float nz = dir.x * sin(rad) + dir.z * cos(rad);
//    at = eye + glm::vec3(nx, dir.y, nz);
//}

// 뷰 행렬 반환 함수
glm::mat4 Camera::GetView() const
{
    return glm::lookAt(eye, at, up);
}

// 투영 행렬 반환 함수
glm::mat4 Camera::GetProj(float aspect) const
{
    return glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.f);
}
