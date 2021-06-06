// OpenGL3Dtn_mai.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "Src/TitleScene.h"
#include <iostream>

// 課題1push, pop関数を実装しよう
//int score[10] = { 0,0,0,0,0,0,0,0,0,0 };
//int cnt = 0;
//void push(const int& i)
//{
//    score[cnt] = i;
//    ++cnt;
//}
//const int pop()
//{
//    --cnt;
//    return score[cnt];
//}

int main()
{
    //std::cout << "Hello World!\n";

    //// 課題1push, pop関数を実装しよう
    //push(10);
    //push(30);
    //std::cout << pop() << "\n";
    //push(20);
    //push(100);
    //pop();
    //std::cout << pop() << "\n";
    //std::cout << pop() << "\n";

    SceneStack& sceneStack = SceneStack::Instance();
    // ↓sceneStack.Push(std::shared_ptr<TitleScene>(new TitleScene);と同じ
    sceneStack.Push(std::make_shared<TitleScene>());

    for (;;)
    {
        const float deltaTime = 1.0f / 60.0f;
        sceneStack.Update(deltaTime);
        sceneStack.Render();
    }
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
