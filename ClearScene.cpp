#include "ClearScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"

void ClearScene::Initialize()
{
	_clearImage = GraphFactory::Instance().LoadGraph("img\\clear.png");
}

void ClearScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\clear.png");
}

void ClearScene::Update()
{
	DrawGraph(0, 0, _clearImage, FALSE);

	//スペースキーを押したらゲーム開始
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		//シーンをゲームシーンに切り替える
		SceneManager::Instance().LoadScene("Title");
	}
}
