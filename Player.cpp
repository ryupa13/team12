#include <DxLib.h>
#include "Player.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "Input.h"

//	����������
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

//	�`��
void Player::Render()
{
	//	�v���C���[��`��
	Renderer::Instance().DrawGraph(_grp, _position, _rectPosition, _size);
}

//	�X�V
void Player::Update()
{
	//	�ړ��ʂ��N���A	
	_velocity.Zero();

	float speed = 3;
	_velocity = Input::Velocity() * speed;
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

