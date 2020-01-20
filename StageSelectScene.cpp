#include "StageSelectScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"
#include "TileMap.h"

void StageSelectScene::Initialize()
{
	//選択画面の背景の画像読み込み
	_selectImage = GraphFactory::Instance().LoadGraph("img\\select.png");
	//四角画像
	_squareImage = GraphFactory::Instance().LoadGraph("img\\square.png");
	//枠画像
	_frameImage = GraphFactory::Instance().LoadGraph("img\\frame.png");

	//カーソルを合わせているステージ番号
	_stageNumber = 0;
	//ステージ番号の上限
	_stageNumberLimit = 2;
}

void StageSelectScene::Update()
{
	//背景を表示する
	Renderer::Instance().DrawGraph(_selectImage, Vector2(0, 0));
	//ステージ一覧を表示する
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 64 * 4, WindowInfo::WindowHeight / 2 - 64));
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 64, WindowInfo::WindowHeight / 2 - 64));
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 + 64 * 2, WindowInfo::WindowHeight / 2 - 64));

	//Zキーが押されたら
	if (Input::GetKeyTrigger(KEY_INPUT_Z))
	{
		//カーソルを合わせていたステージ番号に応じてマップを読み込む
		switch (_stageNumber)
		{
		case 0:
			TileMap::Instance().Start("stage\\stage01.csv");
			break;
		case 1:
			TileMap::Instance().Start("stage\\stage02.csv");
			break;
		case 2:
			TileMap::Instance().Start("stage\\stage03.csv");
			break;
		default:
			break;
		}

		//シーンをゲームシーンに切り替える
		SceneManager::Instance().LoadScene("Game");
	}

	//カーソル移動、ステージ番号の上下
	if (Input::GetKeyTrigger(KEY_INPUT_RIGHT))
	{
		_stageNumber += 1;

		if (_stageNumber > _stageNumberLimit)
			_stageNumber = _stageNumberLimit;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_LEFT))
	{
		_stageNumber -= 1;

		if (_stageNumber < 0)
			_stageNumber = 0;
	}

	//カーソルの描画
	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 64 * 4 + 64 * _stageNumber * 3, WindowInfo::WindowHeight / 2 - 64));
}

void StageSelectScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\select.png");
	GraphFactory::Instance().EraseGraph("img\\square.png");
	GraphFactory::Instance().EraseGraph("img\\frame.png");
}