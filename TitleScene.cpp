#include "TitleScene.h"
#include"DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"

//初期化
void TitleScene::Initialize()
{
	//タイトルの背景の画像読み込み
	_titleImage = GraphFactory::Instance().LoadGraph("img\\pipo-battlebg018b.jpg");
}

//更新
void TitleScene::Update()
{
	//タイトル画面を表示する
	DrawGraph(0, 0, _titleImage, FALSE);

	//キー入力を更新
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//スペースキーを押したらゲーム開始
	if (key & PAD_INPUT_10)
	{
		//シーンをゲームシーンに切り替える
		SceneManager::Instance().LoadScene("Game");
	}
}

//解放
void TitleScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\pipo-battlebg018b.jpg");
}
