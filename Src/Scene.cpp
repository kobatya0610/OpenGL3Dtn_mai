/*
@file Scene.cpp
*/
#include "Scene.h"
#include <iostream>

/*
コンストラクタ

@param name シーン名
*/
Scene::Scene(const char* name):name(name)
{
}

/*
デストラクタ
*/
Scene::~Scene()
{
	Finalize();
}

/*
シーンを活動状態にする
*/
void Scene::Play()
{
	isActive = true;
}

/*
シーンを停止状態にする
*/
void Scene::Stop()
{
	isActive = false;
}

/*
シーンを非表示にする
*/
void Scene::Hide()
{
	isVisible = false;
}

/*
シーン名を取得する

@return シーン名
*/
const std::string& Scene::Name() const
{
	return name;
}

/*
シーンの活動状態を調べる

@return true 活動中
@return false 活動停止中
*/
bool Scene::IsVisible() const
{
	return isVisible;
}