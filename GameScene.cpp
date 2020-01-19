#include "GameScene.h"
#include <DxLib.h>
#include "GraphFactory.h"
#include "SceneManager.h"
#include "WindowInfo.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SmallEnemy.h"
#include "TileMap.h"

void GameScene::Initialize()
{
	GameObjectManager::Instance().Start();
	GameObjectManager::Instance().Add(new Player());
	GameObjectManager::Instance().Add(new Enemy(0, Vector2(64 * 5, 64 * 4)));
	GameObjectManager::Instance().Add(new Enemy(1, Vector2(64 * 9, 64 * 9)));
	GameObjectManager::Instance().Add(new SmallEnemy(2, Vector2(64 * 11, 64)));
}

void GameScene::Update()
{
	//更新
	GameObjectManager::Instance().Update();

	//描画
	TileMap::Instance().Render();
	GameObjectManager::Instance().Render();

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

}
