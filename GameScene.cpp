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



void GameScene::Initialize()
{
	GameObjectManager::Instance().Start();
	GameObjectManager::Instance().Add(new Player());

	switch (TileMap::Instance().GetMapNumber())
	{
	case 0:
		GameObjectManager::Instance().Add(new Enemy(0, Vector2(64 * 5, 64 * 4)));
		GameObjectManager::Instance().Add(new Enemy(1, Vector2(64 * 9, 64 * 9)));
		GameObjectManager::Instance().Add(new SmallEnemy(2, Vector2(64 * 11, 64)));
		break;
	case 1:
		GameObjectManager::Instance().Add(new Enemy(0, Vector2(64 * 6, 64 * 4)));
		GameObjectManager::Instance().Add(new Enemy(1, Vector2(64 * 8, 64 * 8)));
		GameObjectManager::Instance().Add(new SmallEnemy(2, Vector2(64 * 10, 64 * 2)));
		break;
	case 2:
		GameObjectManager::Instance().Add(new Enemy(0, Vector2(64 * 7, 64 * 4)));
		GameObjectManager::Instance().Add(new Enemy(1, Vector2(64 * 10, 64 * 9)));
		GameObjectManager::Instance().Add(new SmallEnemy(2, Vector2(64 * 15, 64)));
		break;
	default:
		break;
	}
}

void GameScene::Update()
{
	//更新
	GameObjectManager::Instance().Update();

	//描画
	TileMap::Instance().Render();
	GameObjectManager::Instance().Render();
	
	for (int i = 1; i < GameObjectManager::Instance().GetBulletCnt() + 1; i++)
	{
		Renderer::Instance().DrawGraph(_gameImage, Vector2(WindowInfo::WindowWidth - i * 64, 0), Vector2(0, 0), Vector2(64, 64));
	}
//タイルマップとの当たり判定
	GameObjectManager::Instance().TileMapCollision();

	if (GameObjectManager::Instance().GetClearFlag())
	{
		SceneManager::Instance().LoadScene("Clear");
	}
	if (GameObjectManager::Instance().GetDeadFlag())
	{
		SceneManager::Instance().LoadScene("Gameover");
	}

}

void GameScene::Release()
{

}
