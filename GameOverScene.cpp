#include "GameOverScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"

void GameOverScene::Initialize()
{
	
	_gameoverImage = GraphFactory::Instance().LoadGraph("img\\overkari.png");
	//枠画像
	_frameImage = GraphFactory::Instance().LoadGraph("img\\waku.png");

	//カーソル番号
	_cursorNumber = 0;
}

void GameOverScene::Update()
{
	//背景を表示する
	Renderer::Instance().DrawGraph(_gameoverImage, Vector2());
	
	
	//SPACEキーが押されたら
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		switch (_cursorNumber)
		{
		case 0: //リトライ
			SceneManager::Instance().LoadScene("Game");
			break;
		case 1: //タイトル
			SceneManager::Instance().LoadScene("Title");
			break;
		case 2: //ステージ選択
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

		if (_cursorNumber > 2)
			_cursorNumber = 2;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_UP))
	{
		_cursorNumber -= 1;

		if (_cursorNumber < 0)
			_cursorNumber = 0;
	}

	//カーソルの描画

	//Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 450, 194 + _cursorNumber * 170));

	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 + 197, 268 + _cursorNumber * 138));

}

void GameOverScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\overkari.png");
	GraphFactory::Instance().EraseGraph("img\\waku.png");
}
