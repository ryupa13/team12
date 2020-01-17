#include "TitleScene.h"
#include"DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"

//初期化
void TitleScene::Initialize()
{
	//タイトルの背景の画像読み込み
	_titleImage = GraphFactory::Instance().LoadGraph("img\\title.png");
}

//更新
void TitleScene::Update()
{
	//タイトル画面を表示する
	DrawGraph(0, 0, _titleImage, FALSE);

	//スペースキーを押したらゲーム開始
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		//シーンをステージ選択シーンに切り替える
		SceneManager::Instance().LoadScene("Select");
	}
}

//解放
void TitleScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\title.png");
}
