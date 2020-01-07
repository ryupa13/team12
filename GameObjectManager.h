#pragma once
#include <list>
#include "GameObject.h"
#include "Collision.h"
#include "Player.h"

class GameObjectManager
{
private:
	GameObjectManager() {}
	GameObjectManager(const GameObjectManager&) {}
	GameObjectManager& operator = (const GameObjectManager&) {}

public:
	//デストラクタ
	~GameObjectManager();

	//インスタンスを取得
	static GameObjectManager& Instance();

	//開始
	void Start();

	//更新
	void Update();

	//描画
	void Render();

	//GameObjectを追加する
	void Add(GameObject* gameObject);

	//タイルマップの衝突判定
	void TileMapCollision(bool hitX, bool hitY);

	Vector2 GetPlayerPosition();
	Vector2 GetPlayerSize();
	Vector2 GetPlayerVelocity();

private:
	//プレイヤーとエネミーの当たり判定
	void HitToCharacters();

	//ブロックとの当たり判定
	void HitToBlocks();

	//エネミー同士の当たり判定
	void HitToEnemys();

	//死亡オブジェクトの削除
	void RemoveDeadGameObjects();

private:
	std::list<GameObject*> _players; //プレイヤーリスト
	std::list<GameObject*> _enemys;  //エネミーリスト
	std::list<GameObject*> _blocks;  //ブロックリスト
	std::list<GameObject*> _addNewGameObjects; //追加するゲームオブジェクトリスト

	Collision _collision;
};