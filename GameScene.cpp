#include "GameScene.h"
#include <DxLib.h>
#include "GraphFactory.h"
#include "SceneManager.h"
#include "WindowInfo.h"

void GameScene::Initialize()
{
	//タイトルの背景の画像読み込み
	_gameImage = GraphFactory::Instance().LoadGraph("img\\pipo-battlebg001b.jpg");

	_tileMap.Start();
	_player.Start();
	HitX = false;
	HitY = false;
}

void GameScene::Update()
{
	//タイトル画面を表示する
	//DrawGraph(0, 0, _gameImage, FALSE);

	_player.Update();
	auto info = _tileMap.FindTileHitInfo(_player.Position(), _player.Size(), _player.Velocity());
	_player.UpdatePosition(info._hitX, info._hitY);

	_tileMap.Render();
	_player.Render();

	if (info._hitX == 1 || info._hitY == 1)
	{
		if (info._no == 80)
		{
			//シーンをゲームシーンに切り替える
			SceneManager::Instance().LoadScene("Clear");
		}
	}

	if (info._hitX == 1)
	{
		HitX = true;
	}
	else HitX = false;

	if (info._hitY == 1)
	{
		HitY = true;
	}
	else HitY = false;

#ifdef _DEBUG_
	DrawFormatString(20, 50, GetColor(255, 255, 255), "HitX : %d HitY : %d No : %d ", info._hitX, info._hitY, info._no);
#endif	


	//キー入力を更新
	//int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	////スペースキーを押したらゲーム開始
	//if (key & PAD_INPUT_10)
	//{
	//	//シーンをゲームシーンに切り替える
	//	SceneManager::Instance().LoadScene("Clear");
	//}
}

void GameScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\pipo-battlebg001b.jpg");
}
