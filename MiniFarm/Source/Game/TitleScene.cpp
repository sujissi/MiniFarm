#include "PCH.h"
#include "TitleScene.h"
#include "TextRenderer.h"
#include "SceneManager.h"
#include "IngameScene.h"
#include "InputManager.h"

void TitleScene::Init()
{
	SetClearColor(glm::vec3(1, 1, 1));
}

void TitleScene::Update(int dt)
{
	if (InputManager::IsKeyPressed('\r')) // Enter
	{
		SceneManager::SetScene(std::make_unique<IngameScene>());
	}
}

void TitleScene::Draw()
{
	TextRenderer::Draw("MiniFarm", WINDOW_W / 2, WINDOW_H / 2, 5, { 1,1,0 });
	TextRenderer::Draw("Press [Enter] to start", WINDOW_W / 2, WINDOW_H / 2 - 50, 2, { 1,1,1 });
}
