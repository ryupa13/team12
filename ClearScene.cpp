#include "ClearScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"

void ClearScene::Initialize()
{
	//背景画像
	_clearImage = GraphFactory::Instance().LoadGraph("img\\clear.png");
	//四角画像
	_squareImage = GraphFactory::Instance().LoadGraph("img\\square2.png");
	//枠画像
	_frameImage = GraphFactory::Instance().LoadGraph("img\\frame2.png");

	//カーソル番号
	_cursorNumber = 0;
}

void ClearScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\clear.png");
	GraphFactory::Instance().EraseGraph("img\\square2.png");
	GraphFactory::Instance().EraseGraph("img\\frame2.png");
}

void ClearScene::Update()
{
	//背景を表示する
	Renderer::Instance().DrawGraph(_clearImage, Vector2());
	//選択肢を表示する
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 450, 364));
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 450, 534));

	//Zキーが押されたら
	if (Input::GetKeyTrigger(KEY_INPUT_Z))
	{
		switch (_cursorNumber)
		{
		case 0: //タイトル
			SceneManager::Instance().LoadScene("Title");
			break;
		case 1: //ステージ選択
			SceneManager::Instance().LoadScene("Select");
			break;
		default:
			break;
		}
	}

	//カーソルの移動
	if (Input::GetKeyTrigger(KEY_INPUT_DOWN))
	{
		_cursorNumber += 1;

		if (_cursorNumber > 1)
			_cursorNumber = 1;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_UP))
	{
		_cursorNumber -= 1;

		if (_cursorNumber < 0)
			_cursorNumber = 0;
	}

	//カーソルの描画
	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 450, 364 + _cursorNumber * 170));
}
