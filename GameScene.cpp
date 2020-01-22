#include "GameScene.h"
#include <DxLib.h>
#include "GraphFactory.h"
#include "SceneManager.h"
#include "WindowInfo.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SmallEnemy.h"
#include "TileMap.h"
#include"Renderer.h"
#include"Sound.h"



void GameScene::Initialize()
{	
	GameObjectManager::Instance().Start();
	GameObjectManager::Instance().Add(new Player());

	_gameImage = GraphFactory::Instance().LoadGraph("img\\sumi.png");
	_animFrameCount = 0;
	//BGM再生
	Sound::Instance().PlayBGM("sound\\bgm\\game2.mp3", DX_PLAYTYPE_LOOP);

	switch (TileMap::Instance().GetMapNumber())
	{
	case 0:
		GameObjectManager::Instance().Add(new Enemy(0, Vector2(64 * 5, 64 * 4)));
		GameObjectManager::Instance().Add(new Enemy(1, Vector2(64 * 9, 64 * 9)));
		GameObjectManager::Instance().Add(new SmallEnemy(2, Vector2(64 * 11, 64)));
		Sound::Instance().PlayBGM("sound\\bgm\\game2.mp3", DX_PLAYTYPE_LOOP);
		break;
	case 1:
		GameObjectManager::Instance().Add(new Enemy(0, Vector2(64 * 6, 64 * 4)));
		GameObjectManager::Instance().Add(new Enemy(1, Vector2(64 * 8, 64 * 8)));
		GameObjectManager::Instance().Add(new SmallEnemy(2, Vector2(64 * 10, 64 * 2)));
		Sound::Instance().PlayBGM("sound\\bgm\\game.mp3", DX_PLAYTYPE_LOOP);
		break;
	case 2:
		GameObjectManager::Instance().Add(new Enemy(0, Vector2(64 * 7, 64 * 4)));
		GameObjectManager::Instance().Add(new Enemy(1, Vector2(64 * 10, 64 * 9)));
		GameObjectManager::Instance().Add(new SmallEnemy(2, Vector2(64 * 15, 64)));
		Sound::Instance().PlayBGM("sound\\bgm\\title.mp3", DX_PLAYTYPE_LOOP);
		break;
	case 3:
		GameObjectManager::Instance().Add(new Enemy(0, Vector2(64 * 5, 64 * 4)));
		GameObjectManager::Instance().Add(new Enemy(1, Vector2(64 * 9, 64 * 9)));
		GameObjectManager::Instance().Add(new SmallEnemy(2, Vector2(64 * 11, 64)));
		break;
	default:
		break;
	}
	//count = 0;
}

void GameScene::Update()
{
	//更新
	GameObjectManager::Instance().Update();

	//描画
	TileMap::Instance().Render();
	GameObjectManager::Instance().Render();
	
	_animFrameCount++;

	auto sheetNo = _animFrameCount / AnimationSpeed;
	_offset.x = (sheetNo % HorizonSheet) * 64;
	_offset.y = ((sheetNo / HorizonSheet) % VerticalSheet) * 64;

	for (int i = 1; i < GameObjectManager::Instance().GetBulletCnt() + 1; i++)
	{
		Renderer::Instance().DrawGraph(_gameImage, Vector2(WindowInfo::WindowWidth - i * 64, 0), Vector2(_offset.x, _offset.y), Vector2(64, 64));
	}
//タイルマップとの当たり判定
	GameObjectManager::Instance().TileMapCollision();

	if (GameObjectManager::Instance().GetClearFlag())
	{
		if (TileMap::Instance().GetMapNumber() == 3)
			SceneManager::Instance().LoadScene("Title");
		else
			SceneManager::Instance().LoadScene("Clear");
	}
	if (GameObjectManager::Instance().GetDeadFlag())
	{
		if (TileMap::Instance().GetMapNumber() == 3)
			SceneManager::Instance().LoadScene("Title");
		else
			SceneManager::Instance().LoadScene("Gameover");
	}

}

void GameScene::Release()
{
	Sound::Instance().StopBGM();
}
