#include "PCH.h"
#include "Shader.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "DataTableManager.h"
#include "Player.h"

void main(int argc, char** argv) {

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
    glutInitWindowSize(WINDOW_W, WINDOW_H); // 윈도우 크기 설정
	glutCreateWindow("MiniFarm"); // 윈도우 이름지정 후 생성

	glewInit(); // GLEW 초기화
	glEnable(GL_DEPTH_TEST); // 깊이버퍼 활성화
	glClearColor(1, 1, 1, 1); // 배경색 흰색으로 설정
   
    Shader::Init("Shaders/vertex.glsl", "Shaders/fragment.glsl"); // 쉐이더 초기화
    SceneManager::Init(); // 씬 매니저 초기화
	InputManager::Init(); // 입력 매니저 초기화
    DataTableManager::Init(); // 데이터 테이블 초기화

    SceneManager::AddObject(std::make_shared<Player>()); // 플레이어 오브젝트 추가

    // 콜백 함수들
	glutDisplayFunc(SceneManager::Draw); // 그리기
    glutReshapeFunc(SceneManager::Reshape); // 다시 그리기
	glutKeyboardFunc(InputManager::KeyDown); // 키 다운
    glutKeyboardUpFunc(InputManager::KeyUp); // 키 업
    glutTimerFunc(FRAME_TIME_MS, SceneManager::Update, 0); // 타이머 업데이트

    glutMainLoop();
}
