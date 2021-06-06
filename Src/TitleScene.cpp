/*
@file TitleScene.cpp
*/
#include "TitleScene.h"
#include "MainGameScene.h"

/*
プレイヤーの入力を処理する
*/
void TitleScene::ProcessInput()
{
	// TitleSceneのデータが必要になることは少ないので、リプレース関数を利用している
	SceneStack::Instance().Replace(std::make_shared<MainGameScene>());
}