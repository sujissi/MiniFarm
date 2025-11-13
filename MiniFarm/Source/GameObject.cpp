#include "PCH.H"
#include "GameObject.h"
#include "Shader.h"

// 오브젝트 그리기 함수
void GameObject::Draw()
{
	// 모델이 없으면 리턴
    if (!m_model) return;
	// 모델 행렬 계산
    glm::mat4 modelMat =
		Translate(m_pos) // 이동
		* Rotate(m_rot.y, { 0,1,0 }) // y축 회전
		* Rotate(m_rot.x, { 1,0,0 }) // x축 회전
		* Rotate(m_rot.z, { 0,0,1 }) // z축 회전
		* Scale(m_scale); // 크기 조절
	// 쉐이더에 모델 행렬 설정
    Shader::SetModel(modelMat);
	// 모델 그리기
    m_model->Draw();
}
