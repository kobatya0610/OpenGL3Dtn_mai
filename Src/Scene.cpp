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
	std::cout << "Scene コンストラクタ：" << name << "\n";
}

/*
デストラクタ
*/
Scene::~Scene()
{
	Finalize();
	std::cout << "Scene デストラクタ：" << name << "\n";
}

/*
シーンを活動状態にする
*/
void Scene::Play()
{
	isActive = true;
	std::cout << "Scene Play：" << name << "\n";
}

/*
シーンを停止状態にする
*/
void Scene::Stop()
{
	isActive = false;
	std::cout << "Scene Stop：" << name << "\n";
}

/*
シーンを表示状態にする
*/
void Scene::Show()
{
	isVisible = true;
	std::cout << "Scene Show：" << name << "\n";
}

/*
シーンを非表示にする
*/
void Scene::Hide()
{
	isVisible = false;
	std::cout << "Scene Hide：" << name << "\n";
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
/*
シーンスタックを取得する

@return シーンスタック
*/
SceneStack& SceneStack::Instance()
{
	static SceneStack instance;
	return instance;
}

/*
コンストラクタ
*/
SceneStack::SceneStack()
{
	// シーンの最大数を決める
	// さすがにシーン数が同時に16個も残ることはないと考えての書き方
	stack.reserve(16);
}

/*
シーンをプッシュする

@param p 新しいシーン
*/
void SceneStack::Push(ScenePtr p)
{
	if (!stack.empty())
	{
		Current().Stop();
	}
	stack.push_back(p);
	std::cout << "[シーン プッシュ]" << p->Name() << "\n";
	Current().Initialize();
	Current().Play();
}

/*
シーンをポップする
*/
void SceneStack::Pop()
{
	if (stack.empty()) 
	{
		std::cout << "[シーン ポップ] [警告] シーンスタックが空です.\n";
		return;
	}
	Current().Stop();
	Current().Finalize();
	const std::string sceneName = Current().Name();
	stack.pop_back();
	std::cout << "[シーン ポップ]" << sceneName << "\n";
	// ここで再度中身が入っていないか確認し、入っていればそのシーンを開始する
	if (!stack.empty())
	{
		Current().Play();
	}
}

/*
シーンを置き換える

@param p 新しいシーン
*/
void SceneStack::Replace(ScenePtr p)
{
	std::string sceneName = "(Empty)";
	if (stack.empty())
	{
		std::cout << "[シーン リプレース] [警告] シーンスタックが空です.\n";
	}
	else
	{
		sceneName = Current().Name();
		Current().Stop();
		Current().Finalize();
		stack.pop_back();
	}
	stack.push_back(p);
	std::cout << "[シーン リプレース]" << sceneName << "->" << p->Name() << "\n";
	Current().Initialize();
	Current().Play();
}

/*
現在のシーンを取得する

@return 現在のシーン
*/
Scene& SceneStack::Current()
{
	return *stack.back();
}

/*
現在のシーンを取得する

@return 現在のシーンを取得する
*/
const Scene& SceneStack::Current() const
{
	return *stack.back();
}

/*
シーンの数を取得する

@return スタックに積まれているシーンの数.
*/
size_t SceneStack::Size() const
{
	return stack.size();
}

/*
スタックが空かどうかを調べる

@return true  スタックは空
@return false スタックに1つ以上のシーンが積まれている
*/
bool SceneStack::Empty() const
{
	return stack.empty();
}

/*
シーンを更新する

@param deltaTime 前回の更新からの経過時間(秒)
*/
void SceneStack::Update(float deltaTime)
{
	if (!Empty()) 
	{
		Current().ProcessInput();
	}
	for (ScenePtr& e : stack)
	{
		if (e->IsActive())
		{
			e->Update(deltaTime);
		}
	}
}

/*
シーンを描写する
*/
void SceneStack::Render()
{
	for (ScenePtr& e : stack)
	{
		if (e->IsVisible())
		{
			e->Render();
		}
	}
}