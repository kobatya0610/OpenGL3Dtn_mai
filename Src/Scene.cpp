/*
@file Scene.cpp
*/
#include "Scene.h"
#include <iostream>

/*
�R���X�g���N�^

@param name �V�[����
*/
Scene::Scene(const char* name):name(name)
{
	std::cout << "Scene �R���X�g���N�^�F" << name << "\n";
}

/*
�f�X�g���N�^
*/
Scene::~Scene()
{
	Finalize();
	std::cout << "Scene �f�X�g���N�^�F" << name << "\n";
}

/*
�V�[����������Ԃɂ���
*/
void Scene::Play()
{
	isActive = true;
	std::cout << "Scene Play�F" << name << "\n";
}

/*
�V�[�����~��Ԃɂ���
*/
void Scene::Stop()
{
	isActive = false;
	std::cout << "Scene Stop�F" << name << "\n";
}

/*
�V�[����\����Ԃɂ���
*/
void Scene::Show()
{
	isVisible = true;
	std::cout << "Scene Show�F" << name << "\n";
}

/*
�V�[�����\���ɂ���
*/
void Scene::Hide()
{
	isVisible = false;
	std::cout << "Scene Hide�F" << name << "\n";
}

/*
�V�[�������擾����

@return �V�[����
*/
const std::string& Scene::Name() const
{
	return name;
}

/*
�V�[���̊�����Ԃ𒲂ׂ�

@return true ������
@return false ������~��
*/
bool Scene::IsVisible() const
{
	return isVisible;
}