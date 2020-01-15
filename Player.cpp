#include <DxLib.h>
#include "Player.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "Input.h"

//	����������
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

//	�`��
void Player::Render()
{
	//	�v���C���[��`��
	Renderer::Instance().DrawGraph(_grp, _position, _rectPosition, _size);
	_sumishot.Render();
}


//	�X�V
void Player::Update()
{
	//	�ړ��ʂ��N���A	
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

//�@�q�b�g�ʒm
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

//	���
void Player::Release()
{
}

void Player::UpdatePosition(bool hitX, bool hitY)
{
	//	X�����ɏՓ�
	if (hitX)
		_velocity.x = 0;

	//	Y�����ɏՓ�
	if (hitY)
		_velocity.y = 0;

	_position += _velocity;
}

