/*
@file TitleScene.cpp
*/
#include "TitleScene.h"
#include "MainGameScene.h"
#include "GLFWEW.h"

/*
プレイヤーの入力を処理する
*/
void TitleScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	if (window.GetGamePad().buttonDown & GamePad::START)
	{
		// TitleSceneのデータが必要になることは少ないので、リプレース関数を利用している
		SceneStack::Instance().Replace(std::make_shared<MainGameScene>());
	}
}