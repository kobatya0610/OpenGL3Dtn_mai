/*
@file GameOverScene.cpp
*/
#include "GameOVerScene.h"
#include "TitleScene.h"

/*
プレイヤーの入力を処理する
*/
void GameOverScene::ProcessInput()
{
	SceneStack::Instance().Replace(std::make_shared<TitleScene>());
}