#include "Enemy.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "GameObjectManager.h"

//初期化
void Enemy::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip019b.png");
	_size = Vector2(32, 32);
	_rectPosition = Vector2(0, 32);
	_radius = 16;
	_state = State::Alive;
	_kind = Kind::Enemy;
	_searchPlayerRadius = 320;
}

//描画
void Enemy::Render()
{
	//エネミーの描画
	Renderer::Instance().DrawGraph(_grp, _position, _rectPosition, _size);
}

//更新
void Enemy::Update()
{
	_playerPosition = GameObjectManager::Instance().GetPlayerPosition();

	if (_playerPosition.x - _position.x <= _searchPlayerRadius && _playerPosition.x - _position.x >= -_searchPlayerRadius)
	{
		if (_playerPosition.y - _position.y <= _searchPlayerRadius && _playerPosition.y - _position.y >= -_searchPlayerRadius)
		{
			_velocity = _playerPosition - _position;
			_velocity = _velocity.Normalized();
		}
		else
		{
			_velocity.Zero();
		}
	}
	else
	{
		_velocity.Zero();
	}

	_position += _velocity * 3;
}

//ヒット通知
void Enemy::Hit()
{
	_state = State::Dead;
}

void Enemy::Hit(bool hitX, bool hitY)
{

}

//解放
void Enemy::Release()
{

}