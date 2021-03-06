/*
@file MainGameScene.cpp
*/
#include "MainGameScene.h"
#include "StatusScene.h"
#include "GameOverScene.h"

/*
プレイヤーの入力を処理する
*/
void MainGameScene::ProcessInput()
{
	if (!flag) 
	{
		flag = true;
		SceneStack::Instance().Push(std::make_shared<StatusScene>());
	}
	else
	{
		SceneStack::Instance().Replace(std::make_shared<GameOverScene>());
	}
}