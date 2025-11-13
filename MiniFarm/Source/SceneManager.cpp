#include "PCH.h"
#include "SceneManager.h"
#include "Shader.h"

std::vector<std::shared_ptr<GameObject>> SceneManager::s_objects; // 게임 오브젝트 리스트
Camera SceneManager::s_camera; // 카메라 객체

// 씬 매니저 초기화 함수
void SceneManager::Init()
{
    s_objects.clear(); // 오브젝트 초기화
	s_camera.Init(); // 카메라 초기화
}
// 오브젝트 추가 함수
void SceneManager::AddObject(std::shared_ptr<GameObject> obj)
{
	s_objects.push_back(obj); // 오브젝트 리스트에 추가
}
// 오브젝트 업데이트 함수
void SceneManager::Update(int time)
{
	// 각 오브젝트 업데이트 호출
    for (auto& obj : s_objects)
    {
        obj->Update(time);
    }
    glutPostRedisplay();
    glutTimerFunc(FRAME_TIME_MS, SceneManager::Update, 0);
}
// 오브젝트 그리기 함수
void SceneManager::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Shader::Use(); // 쉐이더 사용
	Shader::SetView(s_camera.GetView()); // 뷰 행렬 설정
	Shader::SetProj(s_camera.GetProj((float)WINDOW_W / WINDOW_H)); // 투영 행렬 설정
	// 각 오브젝트 그리기 호출
    for (auto& obj : s_objects)
        obj->Draw();

    glutSwapBuffers();
}
// 다시 그리기 함수
void SceneManager::Reshape(int w, int h)
{
    glViewport(0, 0, w, h);

}
