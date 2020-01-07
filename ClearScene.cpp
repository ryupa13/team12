#include "ClearScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"

void ClearScene::Initialize()
{
	_clearImage = GraphFactory::Instance().LoadGraph("img\\pipo-battlebg003b.jpg");
}

void ClearScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\pipo-battlebg003b.jpg");
}

void ClearScene::Update()
{
	DrawGraph(0, 0, _clearImage, FALSE);

	//キー入力を更新
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//スペースキーを押したらゲーム開始
	if (key & PAD_INPUT_10)
	{
		//シーンをゲームシーンに切り替える
		SceneManager::Instance().LoadScene("Title");
	}
}
