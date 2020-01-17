#include "DxLib.h"
#include <memory>
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include"Sumi.h"

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
	for (auto s : _sumis)
	{
		delete s;
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
	for (auto s = _sumis.begin(); s != _sumis.end();)
	{
		s = _sumis.erase(s);
		continue;
		++s;
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
		if (newObject->_kind == newObject->Enemy || newObject->_kind == newObject->SmallEnemy)
		{
			_enemys.push_back(newObject);
		}
		if (newObject->_kind == newObject->Block)
		{
			_blocks.push_back(newObject);
		}
		if (newObject->_kind == newObject->Sumi)
		{
			_sumis.push_back(newObject);
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
	HitToEnemys();
	HitToSumis();
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
	for (auto s : _sumis)
	{
		s->Render();
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
	for (auto p = _players.begin(); p != _players.end(); ++p)
	{
		//エネミーで繰り返し
		for (auto e = _enemys.begin(); e != _enemys.end(); ++e)
		{
			//どちらかが死んでたら次へ
			if ((*p)->IsDead() || (*e)->IsDead())
				continue;

			//プレイヤーとエネミーが衝突しているか
			if (_collision.CircleCollision(*p, *e))
			{
				//互いにヒット通知
				(*p)->Hit(*e);
				(*e)->Hit(*p);
			}
		}
	}
}

//ブロックとの当たり判定
void GameObjectManager::HitToBlocks()
{
	//ブロックで繰り返し
	for (auto b = _blocks.begin(); b != _blocks.end(); ++b)
	{
		//プレイヤーで繰り返し
		for (auto p = _players.begin(); p != _players.end(); ++p)
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
		}
		//エネミーで繰り返し
		for (auto e = _enemys.begin(); e != _enemys.end(); ++e)
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
		}
	}
}

//墨の当たり判定
void GameObjectManager::HitToSumis()
{
	//墨で繰り返し
	for (auto s = _sumis.begin(); s != _sumis.end();++s)
	{
		//プレイヤーで繰り返し
		for (auto p = _players.begin(); p != _players.end();++p)
		{
			//同じエネミーなら次へ
			if ((*p) == (*s))
				continue;

			//どちらかが死んでたら次へ
			if ((*p)->IsDead() || (*s)->IsDead())
				continue;

				//プレイヤー同士が衝突しているか
			if (_collision.CircleCollision(*p, *s))
			{
				//お互いにヒット通知
				(*p)->Hit(*s);
				(*s)->Hit(*p);
			}
		}

		for (auto e = _enemys.begin(); e != _enemys.end();++e)
		{
			if ((*s)->IsDead() || (*e)->IsDead())
				continue;
			
			if (_collision.CircleCollision(*s, *e))
			{
				(*e)->Hit(*s);
				(*s)->Hit(*e);
			}
		}
	}
}

//エネミー同士の当たり判定
void GameObjectManager::HitToEnemys()
{
	//エネミーで繰り返し
	for (auto enemy : _enemys)
	{
		//エネミーで繰り返し
		for (auto e : _enemys)
		{
			//同じエネミーなら次へ
			if (enemy->_isEnemy == e->_isEnemy)
				continue;

			//どちらかが死んでたら次へ
			if (enemy->IsDead() || e->IsDead())
				continue;

			//エネミー同士が衝突しているか
			if (_collision.RectCollision(enemy, e))
			{
				//お互いにヒット通知
				enemy->Hit(e);
				e->Hit(enemy);
			}
		}
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

	for (auto s = _sumis.begin();s != _sumis.end(); ++s)
	{
		if ((*s)->IsDead())
		{
			_sumis.erase(s);
			break;
		}
	}
}

void GameObjectManager::TileMapCollision()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
		{
			auto pInfo = TileMap::Instance().FindTileHitInfo((*p).Position(), (*p).Size(), (*p).Velocity());
			p->Hit(pInfo._hitX, pInfo._hitY);

			if (pInfo._hitX == 1 || pInfo._hitY == 1)
			{
				if (pInfo._no == 80)
				{
					p->_state = p->Clear;
				}
			}
		}
	}
	for (auto e : _enemys)
	{
		if (e->_kind == e->Enemy || e->_kind == e->SmallEnemy)
		{
			auto eInfo = TileMap::Instance().FindTileHitInfo((*e).Position(), (*e).Size(), (*e).Velocity());
			e->Hit(eInfo._hitX, eInfo._hitY);
		}
	}
}

Vector2 GameObjectManager::GetPlayerPosition()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
			return p->Position();
	}
	return Vector2(0, 0);
}

Vector2 GameObjectManager::GetPlayerSize()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
			return p->Size();
	}
	return Vector2(0, 0);
}

Vector2 GameObjectManager::GetPlayerVelocity()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
			return p->Velocity();
	}
	return Vector2(0, 0);
}

bool GameObjectManager::GetClearFlag()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
		{
			return p->IsClear();
		}
		return false;
	}
}