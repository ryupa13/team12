#include <DxLib.h>
#include "Player.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "Input.h"

//	初期化処理
void Player::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\player.png");
	_rectSize = Vector2(64, 64);
	_size = Vector2(58, 58);
	_radius = 16;
	_position = Vector2(64, 64);
	_rectPosition = Vector2(0, 64);
	_velocity = Vector2(0, 0);
	_state = State::Alive;
	_kind = Kind::Player;
}

//	描画
void Player::Render()
{
	//	プレイヤーを描画
	Renderer::Instance().DrawGraph(_grp, _position, _rectPosition, _size);
}

//	更新
void Player::Update()
{
	//	移動量をクリア	
	_velocity.Zero();

	float speed = 3;
	_velocity = Input::Velocity() * speed;
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

