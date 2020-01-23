#include "TitleScene.h"
#include"DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Sound.h"
#include "Renderer.h"
#include "WindowInfo.h"
#include "TileMap.h"

//初期化
void TitleScene::Initialize()
{
	//タイトルの背景の画像読み込み

	_titleImage = GraphFactory::Instance().LoadGraph("img\\clear.png");

	//枠画像
	_frameImage = GraphFactory::Instance().LoadGraph("img\\waku.png");
	//SE読み込み
	_titleSE = Sound::Instance().LoadSE("sound\\se\\sentaku.wav");
	_cursorSE = Sound::Instance().LoadSE("sound\\se\\test.wav");
	//BGM再生
	Sound::Instance().PlayBGM("sound\\bgm\\title2.mp3", DX_PLAYTYPE_LOOP);
	//カーソル番号
	_cursorNumber = 0;
}

//更新
void TitleScene::Update()
{
	//タイトル画面を表示する
	Renderer::Instance().DrawGraph(_titleImage, Vector2());

	//スペースキーを押したらゲーム開始
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		switch (_cursorNumber)
		{
		case 0: //ステージ選択
			SceneManager::Instance().LoadScene("Select");
			break;
		case 1: //チュートリアル
			TileMap::Instance().Start("stage\\Tutorial.csv", 3);
			SceneManager::Instance().LoadScene("Game");
			break;
		}
		Sound::Instance().PlaySE(_titleSE, DX_PLAYTYPE_BACK);
		Sound::Instance().StopBGM();
	}

	//カーソルの移動
	if (Input::GetKeyTrigger(KEY_INPUT_DOWN))
	{
		Sound::Instance().PlaySE(_cursorSE, DX_PLAYTYPE_BACK);
		_cursorNumber += 1;

		if (_cursorNumber > 1)
			_cursorNumber = 1;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_UP))
	{
		Sound::Instance().PlaySE(_cursorSE, DX_PLAYTYPE_BACK);
		_cursorNumber -= 1;

		if (_cursorNumber < 0)
			_cursorNumber = 0;
	}

	//カーソルの描画
	//Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 + 197, 268 + _cursorNumber * 138));

	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 162, 362 + _cursorNumber * 138));

}

//解放
void TitleScene::Release()
{

	GraphFactory::Instance().EraseGraph("img\\clear.png");

	GraphFactory::Instance().EraseGraph("img\\waku.png");
}
