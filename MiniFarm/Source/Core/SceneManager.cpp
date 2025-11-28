#include "PCH.h"
#include "SceneManager.h"
#include "IngameScene.h"
#include "TitleScene.h"

std::unique_ptr<Scene> SceneManager::s_currentScene = nullptr;

void SceneManager::Init()
{
	SetScene(std::make_unique<TitleScene>());
}

void SceneManager::Update(int time)
{
	s_currentScene->Update(time);
	glutPostRedisplay();
	glutTimerFunc(FRAME_TIME_MS, SceneManager::Update, 0);
}

void SceneManager::Draw()
{
	glm::vec3 color = s_currentScene->GetClearColor();
	glClearColor(color.r, color.g, color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	s_currentScene->Draw();

	glutSwapBuffers();
}

void SceneManager::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void SceneManager::SetScene(std::unique_ptr<Scene> newScene)
{
	s_currentScene = std::move(newScene);

	if (s_currentScene)
		s_currentScene->Init();
}

Camera& SceneManager::GetCamera()
{
	return s_currentScene->GetCamera();
}

Shader& SceneManager::GetMainShader()
{
	return s_currentScene->GetMainShader();
}

std::vector<std::shared_ptr<GameObject>>& SceneManager::GetObjects()
{
	return s_currentScene->GetObjects();
}