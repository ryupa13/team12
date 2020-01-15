#include <DxLib.h>
#include "Player.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "Input.h"

//	初期化処理
void Player::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip005.png");
	_size = Vector2(32, 32);
	_radius = 16;
	_position = Vector2(64, 64);
	_rectPosition = Vector2(0, 64);
	_velocity = Vector2(0, 0);
	_state = State::Alive;
	_kind = Kind::Player;
	pDirection = PDirection::DOWN;
	

}

//	描画
void Player::Render()
{
	//	プレイヤーを描画
	Renderer::Instance().DrawGraph(_grp, _position, _rectPosition, _size);
	_sumishot.Render();
}


//	更新
void Player::Update()
{
	//	移動量をクリア	
	_velocity.Zero();

	float speed = 3;
	_velocity = Input::Velocity() * speed;
	UpdateMotion();

	if (Input::GetKeyTrigger(KEY_INPUT_Z))
	{
		if (_velocity.Magnitude() <= 0)
		{
			_velocity = _maps[pDirection];
		}
		if (count < 100)
		{
			_sumishot.Shot(_position,_maps[pDirection]);
			count++;
		}
	}
}

void Player::UpdateMotion()
{
	Vector2  velocity = Input::Velocity();
	if (velocity.y > 0.0f && (pDirection != PDirection::DOWN))
	{
		pDirection = PDirection::DOWN;
	}
	else if((velocity.y<0.0f)&& (pDirection != PDirection::UP))
	{
		pDirection = PDirection::UP;
	}
	else if (velocity.x > 0.0f && (pDirection != PDirection::RIGHT))
	{
		pDirection = PDirection::RIGHT;
	}
	else if (velocity.x < 0.0f&& (pDirection != PDirection::LEFT))
	{

		pDirection = PDirection::LEFT;
	}
}

//　ヒット通知
void Player::Hit()
{

}

void Player::Hit(GameObject *hitObject)
{
	if ((*hitObject)._kind == (*hitObject).SmallEnemy)
	{
		_state = State::Clear;
	}
}

void Player::Hit(bool hitX, bool hitY)
{
	UpdatePosition(hitX, hitY);
}

//	解放
void Player::Release()
{
}

void Player::UpdatePosition(bool hitX, bool hitY)
{
	//	X方向に衝突
	if (hitX)
		_velocity.x = 0;

	//	Y方向に衝突
	if (hitY)
		_velocity.y = 0;

	_position += _velocity;
}

