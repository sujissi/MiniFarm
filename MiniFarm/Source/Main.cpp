#include "PCH.h"
#include "Shader.h"
#include "SceneManager.h"
#include "Player.h"

constexpr int FPS = 60;
constexpr int FRAME_TIME_MS = 1000 / FPS;

GLvoid Reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

GLvoid DrawScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SceneManager::Draw();
    glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'q': exit(0);
	}

	glutPostRedisplay();
}

GLvoid Timer(int value) {

    float dt = 1.0f / 60.0f;
    SceneManager::Update(dt);
    glutPostRedisplay();
    glutTimerFunc(FRAME_TIME_MS, Timer, 0);
}

void main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutCreateWindow("MiniFarm");

    glewInit();
    glEnable(GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 1);

    Shader::Init("Shaders/vertex.glsl", "Shaders/fragment.glsl");
    SceneManager::Init();
    SceneManager::AddObject(std::make_shared<Player>());

    glutDisplayFunc(DrawScene);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);

    glutTimerFunc(FRAME_TIME_MS, Timer, 0);

    glutMainLoop();
}
