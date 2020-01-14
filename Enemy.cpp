#include "Enemy.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "GameObjectManager.h"

//初期化
void Enemy::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip019b.png");
	_size = Vector2(63, 63);
	_rectPosition = Vector2(0, 32);
	_radius = 16;
	_state = State::Alive;
	_kind = Kind::Enemy;
	_search = SearchState::Free;
	_searchPlayerRadius = 160;
	_stateCount = 0;
	_hitWallX = false;
	_hitWallY = false;
	_rnd = 1234;
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
	Vector2 centerPosition = _position + Vector2(32, 32);
	Vector2 centerPlayerPosition = _playerPosition + Vector2(32, 32);

	if (centerPlayerPosition.x - centerPosition.x <= _searchPlayerRadius && centerPlayerPosition.x - centerPosition.x >= -_searchPlayerRadius)
	{
		if (centerPlayerPosition.y - centerPosition.y <= _searchPlayerRadius && centerPlayerPosition.y - centerPosition.y >= -_searchPlayerRadius)
		{
			_search = SearchState::Chase;
			_speed = 3;
		}
		else
		{
			_search = SearchState::Free;
			_speed = 2;
			_chaseCount = 0;
		}
	}
	else
	{
		_search = SearchState::Free;
		_speed = 2;
		_chaseCount = 0;
	}

	_velocity.Zero();
	UpdateVelocity();
}

//ヒット通知
void Enemy::Hit()
{
	_state = State::Dead;
}

void Enemy::Hit(GameObject *hitObject)
{
	if ((*hitObject).Enemy || (*hitObject).SmallEnemy)
		return;
	_state = State::Dead;
}

void Enemy::Hit(bool hitX, bool hitY)
{
	UpdatePosition(hitX, hitY);
}

//解放
void Enemy::Release()
{

}

void Enemy::UpdateVelocity()
{
	if (_search == SearchState::Chase)
	{
		_playerPosition = GameObjectManager::Instance().GetPlayerPosition();
		_length = _playerPosition - _position;

		switch (_chaseCount)
		{
		case 0: //方向決定
			//縦横
			if (_length.x > _length.y) //縦
			{
				//プレイヤーの上下どちらかに居るか
				if (_playerPosition.y > _position.y) //上
				{
					_stateCount = 2;
					_chaseCount = 2;
				}
				else //下
				{
					_stateCount = 1;
					_chaseCount = 1;
				}
			}
			else //横
			{
				//プレイヤーの左右どちらかに居るか
				if (_playerPosition.x > _position.x) //左
				{
					_stateCount = 4;
					_chaseCount = 4;
				}
				else //右
				{
					_stateCount = 3;
					_chaseCount = 3;
				}
			}
			break;
		case 1: //上
			_velocity.y = -1;
			//壁に当たっていたら
			if (_hitWallY)
			{
				//プレイヤーの左右どちらかに居るか
				if (_playerPosition.x > _position.x) //左
				{
					_velocity.x = 1;
					_stateCount = 4;
					_chaseCount = 4;

					if (_hitWallX)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = 1;
							_stateCount = 2;
							_chaseCount = 2;
						}
						else
						{
							_velocity.x = -1;
							_stateCount = 3;
							_chaseCount = 3;
						}
					}
				}
				else //右
				{
					_velocity.x = -1;
					_stateCount = 3;
					_chaseCount = 3;

					if (_hitWallX)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = 1;
							_stateCount = 2;
							_chaseCount = 2;
						}
						else
						{
							_velocity.x = 1;
							_stateCount = 4;
							_stateCount = 4;
						}
					}
				}
			}
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			break;
		case 2: //下
			_velocity.y = 1;
			//壁に当たっていたら
			if (_hitWallY)
			{
				//プレイヤーの左右どちらかに居るか
				if (_playerPosition.x > _position.x) //左
				{
					_velocity.x = 1;
					_stateCount = 4;
					_chaseCount = 4;

					if (_hitWallX)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = -1;
							_stateCount = 1;
							_chaseCount = 1;
						}
						else
						{
							_velocity.x = -1;
							_stateCount = 3;
							_chaseCount = 3;
						}
					}
				}
				else //右
				{
					_velocity.x = -1;
					_stateCount = 3;
					_chaseCount = 3;

					if (_hitWallX)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = -1;
							_stateCount = 1;
							_chaseCount = 1;
						}
						else
						{
							_velocity.x = 1;
							_stateCount = 4;
							_chaseCount = 4;
						}
					}
				}
			}
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			break;
		case 3: //左
			_velocity.x = -1;
			//壁に当たっていたら
			if (_hitWallX)
			{
				//プレイヤーの上下どちらかに居るか
				if (_playerPosition.y > _position.y) //上
				{
					_velocity.y = 1;
					_stateCount = 2;
					_chaseCount = 2;

					if (_hitWallY)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = -1;
							_stateCount = 1;
							_stateCount = 1;
						}
						else
						{
							_velocity.x = 1;
							_stateCount = 4;
							_chaseCount = 4;
						}
					}
				}
				else //下
				{
					_velocity.y = -1;
					_stateCount = 1;
					_chaseCount = 1;

					if (_hitWallY)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = 1;
							_stateCount = 2;
							_chaseCount = 2;
						}
						else
						{
							_velocity.x = 1;
							_stateCount = 4;
							_chaseCount = 4;
						}
					}
				}
			}
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			break;
		case 4: //右
			_velocity.x = 1;
			//壁に当たっていたら
			if (_hitWallX)
			{
				//プレイヤーの上下どちらかに居るか
				if (_playerPosition.y > _position.y) //上
				{
					_velocity.y = 1;
					_stateCount = 2;
					_chaseCount = 2;

					if (_hitWallY)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = -1;
							_stateCount = 1;
							_chaseCount = 1;
						}
						else
						{
							_velocity.x = -1;
							_stateCount = 3;
							_chaseCount = 3;
						}
					}
				}
				else //下
				{
					_velocity.y = -1;
					_stateCount = 1;
					_chaseCount = 1;

					if (_hitWallY)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = 1;
							_stateCount = 2;
							_chaseCount = 2;
						}
						else
						{
							_velocity.x = -1;
							_stateCount = 3;
							_chaseCount = 3;
						}
					}
				}
				break;
			}
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
		default:
			break;
		}
	}
	else if (_search == SearchState::Free)
	{
		//自由移動
		switch (_stateCount)
		{
		case 0://最初の移動
			_velocity.x = 1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallX)
			{
				//横壁にぶつかったら
				_stateCount = 1;
			}
			break;
		case 1: //上
			_velocity.y = -1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallY)
			{
				_rnd = GetRand(1);
				if (_rnd == 0)
				{
					_stateCount = 3;
				}
				else
				{
					_stateCount = 4;
				}
			}
			break;
		case 2:	//下
			_velocity.y = 1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallY)
			{
				_rnd = GetRand(1);
				if (_rnd == 0)
				{
					_stateCount = 3;
				}
				else
				{
					_stateCount = 4;
				}
			}
			break;
		case 3: //左
			_velocity.x = -1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallX)
			{
				_rnd = GetRand(1);
				if (_rnd == 0)
				{
					_stateCount = 1;
				}
				else
				{
					_stateCount = 2;
				}
			}
			break;
		case 4: //右
			_velocity.x = 1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallX)
			{
				_rnd = GetRand(1);
				if (_rnd == 0)
				{
					_stateCount = 1;
				}
				else
				{
					_stateCount = 2;
				}
			}
			break;

		default:
			break;
		}
	}
}

void Enemy::UpdatePosition(bool hitX, bool hitY)
{
	//	X方向に衝突
	if (hitX)
	{
		_velocity.x = 0;
		_hitWallX = true;
	}
	else _hitWallX = false;

	//	Y方向に衝突
	if (hitY)
	{
		_velocity.y = 0;
		_hitWallY = true;
	}
	else _hitWallY = false;

	_position += _velocity;
}