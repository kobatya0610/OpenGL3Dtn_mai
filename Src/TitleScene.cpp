/*
@file TitleScene.cpp
*/
#include "TitleScene.h"
#include "MainGameScene.h"

/*
�v���C���[�̓��͂���������
*/
void TitleScene::ProcessInput()
{
	// TitleScene�̃f�[�^���K�v�ɂȂ邱�Ƃ͏��Ȃ��̂ŁA���v���[�X�֐��𗘗p���Ă���
	SceneStack::Instance().Replace(std::make_shared<MainGameScene>());
}