/*
@file GameOverScene.cpp
*/
#include "GameOVerScene.h"
#include "TitleScene.h"

/*
�v���C���[�̓��͂���������
*/
void GameOverScene::ProcessInput()
{
	SceneStack::Instance().Replace(std::make_shared<TitleScene>());
}