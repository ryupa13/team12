#include "DxLib.h"
#include <memory>
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

//デストラクタ
GameObjectManager::~GameObjectManager()
{
	//解放する
	for (auto p : _players)
	{
		delete p;
	}
	for (auto e : _enemys)
	{
		delete e;
	}
	for (auto b : _blocks)
	{
		delete b;
	}
}

//クラスのインスタンスを取得
GameObjectManager & GameObjectManager::Instance()
{
	static std::unique_ptr<GameObjectManager> instance(new GameObjectManager);

	return *instance;
}

//初期化
void GameObjectManager::Start()
{
	for (auto p = _players.begin(); p != _players.end();)
	{
		p = _players.erase(p);
		continue;

		++p;
	}
	for (auto e = _enemys.begin(); e != _enemys.end();)
	{
		e = _enemys.erase(e);
		continue;

		++e;
	}
	for (auto b = _blocks.begin(); b != _blocks.end();)
	{
		b = _blocks.erase(b);
		continue;

		++b;
	}
}

//更新
void GameObjectManager::Update()
{
	for (auto newObject : _addNewGameObjects)
	{
		newObject->Start();
		if (newObject->_kind == newObject->Player)
		{
			_players.push_back(newObject);
		}
		if (newObject->_kind == newObject->Enemy)
		{
			_enemys.push_back(newObject);
		}
		if (newObject->_kind == newObject->Block)
		{
			_blocks.push_back(newObject);
		}
	}

	if (!_addNewGameObjects.empty())
	{
		for (auto a = _addNewGameObjects.begin(); a != _addNewGameObjects.end();)
		{
			a = _addNewGameObjects.erase(a);
			continue;

			++a;
		}
	}

	for (auto p : _players)
	{
		p->Update();
	}
	for (auto e : _enemys)
	{
		e->Update();
	}

	HitToCharacters();

	RemoveDeadGameObjects();
}

//描画
void GameObjectManager::Render()
{
	for (auto p : _players)
	{
		p->Render();
	}
	for (auto e : _enemys)
	{
		e->Render();
	}
}

//追加
void GameObjectManager::Add(GameObject* gameObject)
{
	if (gameObject == nullptr)
		return;

	//追加リストにオブジェクトを追加
	_addNewGameObjects.push_back(gameObject);
}

//プレイヤーとエネミーの当たり判定
void GameObjectManager::HitToCharacters()
{
	//プレイヤーで繰り返し
	for (auto p = _players.begin(); p != _players.end();)
	{
		//エネミーで繰り返し
		for (auto e = _enemys.begin(); e != _enemys.end();)
		{
			//どちらかが死んでたら次へ
			if ((*p)->IsDead() || (*e)->IsDead())
				continue;

			//プレイヤーとエネミーが衝突しているか
			if (_collision.CircleCollision(*p, *e))
			{
				//互いにヒット通知
				(*p)->Hit();
				(*e)->Hit();
			}
			++e;
		}
		++p;
	}
}

//ブロックとの当たり判定
void GameObjectManager::HitToBlocks()
{
	//ブロックで繰り返し
	for (auto b = _blocks.begin(); b != _blocks.end();)
	{
		//プレイヤーで繰り返し
		for (auto p = _players.begin(); p != _players.end();)
		{
			//どちらかが死んでたら次へ
			if ((*b)->IsDead() || (*p)->IsDead())
				continue;

			//ブロックとプレイヤーが衝突しているか
			if (_collision.RectCollision(*b, *p))
			{
				//プレイヤーにヒット通知
				(*p)->Hit();
			}
			++p;
		}
		//エネミーで繰り返し
		for (auto e = _enemys.begin(); e != _enemys.end();)
		{
			//どちらかが死んでたら次へ
			if ((*b)->IsDead() || (*e)->IsDead())
				continue;

			//ブロックとエネミーが衝突しているか
			if (_collision.RectCollision(*b, *e))
			{
				//エネミーにヒット通知
				(*e)->Hit();
			}
			++e;
		}
		++b;
	}
}

//エネミー同士の当たり判定
void GameObjectManager::HitToEnemys()
{
	//エネミーで繰り返し
	for (auto enemy = _enemys.begin(); enemy != _enemys.end();)
	{
		//エネミーで繰り返し
		for (auto e = _enemys.begin(); e != _enemys.end();)
		{
			//同じエネミーなら次へ
			if (enemy == e)
				continue;

			//どちらかが死んでたら次へ
			if ((*enemy)->IsDead() || (*e)->IsDead())
				continue;

			//エネミー同士が衝突しているか
			if (_collision.RectCollision(*enemy, *e))
			{
				//お互いにヒット通知
				(*enemy)->Hit();
				(*e)->Hit();
			}
			++e;
		}
		++enemy;
	}
}

//死亡ゲームオブジェクトの削除
void GameObjectManager::RemoveDeadGameObjects()
{
	//死んでいたらリストから削除
	for (auto p = _players.begin(); p != _players.end();)
	{
		if ((*p)->IsDead())
		{
			p = _players.erase(p);
			continue;
		}
		++p;
	}
	for (auto e = _enemys.begin(); e != _enemys.end();)
	{
		if ((*e)->IsDead())
		{
			e = _enemys.erase(e);
			continue;
		}
		++e;
	}
	for (auto b = _blocks.begin(); b != _blocks.end();)
	{
		if ((*b)->IsDead())
		{
			b = _blocks.erase(b);
			continue;
		}
		++b;
	}
}

void GameObjectManager::TileMapCollision(bool hitX, bool hitY)
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
			return p->Hit(hitX, hitY);
	}
}

Vector2 GameObjectManager::GetPlayerPosition()
{
	for (auto p : _players)
	{
		if (p->_kind == 0)
			return p->Position();
	}
	return Vector2(0, 0);
}

Vector2 GameObjectManager::GetPlayerSize()
{
	for (auto p : _players)
	{
		if (p->_kind == 0)
			return p->Size();
	}
	return Vector2(0, 0);
}

Vector2 GameObjectManager::GetPlayerVelocity()
{
	for (auto p : _players)
	{
		if (p->_kind == 0)
			return p->Velocity();
	}
	return Vector2(0, 0);
}