#include "PCH.h"
#include "Shader.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "DataTable.h"

void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInitWindowPosition(WINDOW_W/2, WINDOW_H/5);
	glutCreateWindow("MiniFarm");

	glewInit();
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);

	SceneManager::Init();
	InputManager::Init();
	DataTable::Init();

	glutKeyboardFunc(InputManager::KeyDown);
	glutKeyboardUpFunc(InputManager::KeyUp);

	glutMouseFunc(InputManager::MouseButton);
	glutPassiveMotionFunc(InputManager::MouseMove);
	glutDisplayFunc(SceneManager::Draw);
	glutReshapeFunc(SceneManager::Reshape);

	glutTimerFunc(FRAME_TIME_MS, SceneManager::Update, 0);

	glutMainLoop();
}
