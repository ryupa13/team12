#include "StageSelectScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"
#include "TileMap.h"
#include"Sound.h"

void StageSelectScene::Initialize()
{
	//選択画面の背景の画像読み込み
	_selectImage = GraphFactory::Instance().LoadGraph("img\\select.png");
	//枠画像
	_frameImage = GraphFactory::Instance().LoadGraph("img\\selectplayer.png");
	//BGM再生
	Sound::Instance().PlayBGM("sound\\bgm\\title2.mp3", DX_PLAYTYPE_LOOP);

	_gamesceneSE = Sound::Instance().LoadSE("sound\\se\\sentaku.wav");
	_gameEXsceneSE = Sound::Instance().LoadSE("sound\\se\\yaro.wav");
	_crr = Sound::Instance().LoadSE("sound\\se\\test.wav");

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
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 64, WindowInfo::WindowHeight / 2 - 64));
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 + 64 * 2, WindowInfo::WindowHeight / 2 - 64));

	
	//SPACEキーが押されたら
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		//カーソルを合わせていたステージ番号に応じてマップを読み込む
		switch (_stageNumber)
		{
		case 0:
			TileMap::Instance().Start("stage\\stage01.csv", 0);
			break;
		case 1:
			TileMap::Instance().Start("stage\\stage02.csv", 1);
			break;
		case 2:
			TileMap::Instance().Start("stage\\stage03.csv", 2);
			break;
		case 3:
			TileMap::Instance().Start("stage\\stage04.csv", 4);
			break;
		default:
			break;
		}

		//シーンをゲームシーンに切り替える
		SceneManager::Instance().LoadScene("Game");
		Sound::Instance().PlaySE(_gamesceneSE, DX_PLAYTYPE_BACK);
		Sound::Instance().StopBGM();
	}

	if (Input::GetKeyTrigger(KEY_INPUT_H))
	{
		Sound::Instance().PlaySE(_gameEXsceneSE, DX_PLAYTYPE_BACK);
		_stageNumber = 3;
	}

	if (Input::GetKeyTrigger(KEY_INPUT_DOWN))
	{
		Sound::Instance().PlaySE(_crr, DX_PLAYTYPE_BACK);
		_stageNumber += 1;

		if (_stageNumber > _stageNumberLimit)
			_stageNumber = _stageNumberLimit;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_UP))
	{
		Sound::Instance().PlaySE(_crr, DX_PLAYTYPE_BACK);
		_stageNumber -= 1;

		if (_stageNumber < 0)
			_stageNumber = 0;
	}

	//カーソルの描画

	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 128, WindowInfo::WindowHeight / 2 - 150 + _stageNumber * 150));

}

void StageSelectScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\select.png");

	GraphFactory::Instance().EraseGraph("img\\selectplayer.png");
}