#include <DxLib.h>
#include "Player.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "Input.h"
#include"GameObjectManager.h"
//	初期化処理
void Player::Start()
{
	_grp = LoadDivGraph("img\\player.png", 8, 2, 4, 64, 64, anime);
	_rectSize = Vector2(64, 64);
	_size = Vector2(58, 58);
	_radius = 16;
	_position = Vector2(64, 64);
	_rectPosition = Vector2(0, 64);
	_velocity = Vector2(0, 0);
	_state = State::Alive;
	_kind = Kind::Player;
	pDirection = PDirection::DOWN;
	anime[8] = { 0 };
	count = 0;
	ImgIndex = 0;
	animenum = 0;
}

//	描画
void Player::Render()
{
	ImgIndex = count % 20;
	ImgIndex /= 10;
	count += 1;

	DrawGraph(_position.x, _position.y, anime[ImgIndex + (2 * animenum)], TRUE);

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
		
		if ( GameObjectManager::Instance().GetBulletCnt() >0)
		{
			_sumishot.Shot(_position,_maps[pDirection]);
		}
	}
		
	
}

void Player::UpdateMotion()
{
	Vector2  velocity = Input::Velocity();
	if (velocity.y > 0.0f && (pDirection != PDirection::DOWN))
	{
		pDirection = PDirection::DOWN;
		animenum = 2;
	}
    if((velocity.y<0.0f)&& (pDirection != PDirection::UP))
	{
		pDirection = PDirection::UP;
		animenum = 3;

	}
	if (velocity.x > 0.0f && (pDirection != PDirection::RIGHT))
	{
		pDirection = PDirection::RIGHT;
		animenum = 0;
	}
	if (velocity.x < 0.0f&& (pDirection != PDirection::LEFT))
	{
		pDirection = PDirection::LEFT;
		animenum = 1;
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
	if ((*hitObject)._kind == (*hitObject).Enemy)
	{
		_state = State::Dead;
	}
}

void Player::Hit(bool hitX, bool hitY)
{
	UpdatePosition(hitX, hitY);
}

//	解放
void Player::Release()
{
	DeleteGraph(_grp);
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

