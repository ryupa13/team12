#include "SmallEnemy.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "GameObjectManager.h"

//初期化
void SmallEnemy::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip010.png");
	_size = Vector2(32, 32);
	_rectPosition = Vector2(0, 32);
	_radius = 16;
	_state = State::Alive;
	_kind = Kind::SmallEnemy;
	_search = SearchState::Free;
	_searchPlayerRadius = 320;
	_stateCount = 0;
	_hitWallX = false;
	_hitWallY = false;
	_rnd = 1234;
}

//描画
void SmallEnemy::Render()
{
	//エネミーの描画
	Renderer::Instance().DrawGraph(_grp, _position, _rectPosition, _size);
}

//更新
void SmallEnemy::Update()
{
	_playerPosition = GameObjectManager::Instance().GetPlayerPosition();

	if (_playerPosition.x - _position.x <= _searchPlayerRadius && _playerPosition.x - _position.x >= -_searchPlayerRadius)
	{
		if (_playerPosition.y - _position.y <= _searchPlayerRadius && _playerPosition.y - _position.y >= -_searchPlayerRadius)
		{
			_search = SearchState::Chase;
		}
		else
		{
			_search = SearchState::Free;
		}
	}
	else
	{
		_search = SearchState::Free;
	}

	_velocity.Zero();
	UpdateVelocity();
}

//ヒット通知
void SmallEnemy::Hit()
{
	_state = State::Dead;
}

void SmallEnemy::Hit(GameObject *hitObject)
{

}

void SmallEnemy::Hit(bool hitX, bool hitY)
{
	UpdatePosition(hitX, hitY);
}

//解放
void SmallEnemy::Release()
{

}

void SmallEnemy::UpdateVelocity()
{
	if (_search == SearchState::Chase)
	{
		_playerPosition = GameObjectManager::Instance().GetPlayerPosition();
		_velocity = _playerPosition - _position;
		if(_velocity.Magnitude() != 0)
			_velocity = _velocity.Normalized();
		_velocity = _velocity * -3;
	}
	else if (_search == SearchState::Free)
	{
		//自由移動
		switch (_stateCount)
		{
		case 0://最初の移動
			_velocity.x -= 1;
			if (_hitWallX == true)
			{
				//横壁にぶつかったら
				_stateCount = 1;
			}
			break;
		case 1://方向決定
			//変数にランダムな値を格納
			_rnd = GetRand(1);
			_stateCount = 2;
			break;
		case 2:	//縦移動
			if (_rnd == 0)
			{
				_velocity.y += 1;
			}
			else if (_rnd == 1)
			{
				_velocity.y -= 1;
			}

			if (_hitWallY == true)
			{
				//縦壁にぶつかったら
				_stateCount = 3;
			}
			break;
		case 3://方向決定
			//変数にランダムな値を格納
			_rnd = GetRand(1);
			_stateCount = 4;
			break;
		case 4: //横移動
			if (_rnd == 0)
			{
				_velocity.x += 1;
			}
			else if (_rnd == 1)
			{
				_velocity.x -= 1;
			}

			//縦壁にぶつかったら
			if (_hitWallX == true)
			{
				_stateCount = 1;
			}
			break;

		default:
			break;
		}
	}
}

void SmallEnemy::UpdatePosition(bool hitX, bool hitY)
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