#include "PCH.h"
#include "Shader.h"
#include "SceneManager.h"
#include "Player.h"

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
    Input::Init();

    SceneManager::AddObject(std::make_shared<Player>());

    glutDisplayFunc(SceneManager::Draw);
    glutReshapeFunc(SceneManager::Reshape);
    glutKeyboardFunc(Input::KeyDown);
    glutKeyboardUpFunc(Input::KeyUp);
    glutTimerFunc(FRAME_TIME_MS, SceneManager::Update, 0);

    glutMainLoop();
}
