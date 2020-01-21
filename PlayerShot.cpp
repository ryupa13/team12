#include "PlayerShot.h"

PlayerShot::~PlayerShot()
{
	//リストの中身を削除
	for (auto shot : _shotList)
	{
		delete shot;
	}
}

void PlayerShot::Shot(const Vector2 & pos)
{
	//メモリ内に弾を生成する
	Bullet* shot = new Bullet(pos);

	//生成された弾の初期化
	shot->Start();

	//生成・初期化された弾を、リストに格納する。
	_shotList.push_back(shot);
}

void PlayerShot::Update()
{
	//イテレータを使い、リストの最初から最後までを一括管理
	for (auto it = _shotList.begin(); it != _shotList.end();)
	{
		(*it)->Update();

		if ((*it)->GetPosition().x > WindowInfo::WindowWidth)
		{
			delete *it;
			it = _shotList.erase(it);
			continue;
		}
		++it;
	}
}

void PlayerShot::Render()
{
	for (auto shot : _shotList)
	{
		shot->Render();
	}
}
