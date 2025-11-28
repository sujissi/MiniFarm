#include "PCH.h"
#include "SceneManager.h"
#include "IngameScene.h"

std::unique_ptr<Scene> SceneManager::s_currentScene = nullptr;

void SceneManager::Init()
{
	SetScene(std::make_unique<IngameScene>());
}

void SceneManager::Update(int time)
{
	s_currentScene->Update(time);
}

void SceneManager::Draw()
{
	s_currentScene->Draw();
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