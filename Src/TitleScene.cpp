/*
@file TitleScene.cpp
*/
#include "TitleScene.h"
#include "MainGameScene.h"
#include "GLFWEW.h"

/*
�v���C���[�̓��͂���������
*/
void TitleScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	if (window.GetGamePad().buttonDown & GamePad::START)
	{
		// TitleScene�̃f�[�^���K�v�ɂȂ邱�Ƃ͏��Ȃ��̂ŁA���v���[�X�֐��𗘗p���Ă���
		SceneStack::Instance().Replace(std::make_shared<MainGameScene>());
	}
}