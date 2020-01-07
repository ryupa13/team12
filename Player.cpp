#include <DxLib.h>
#include "Player.h"
#include "GraphFactory.h"
#include "Renderer.h"

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
	//	�L�[���͂��X�V
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//	�ړ��ʂ��N���A	
	_velocity.Zero();

	// ��L�[�őO�ɐi��
	if (key & PAD_INPUT_UP) {
		_velocity.y -= 2;
	}

	//	���L�[�Ō��ɐi��
	if (key & PAD_INPUT_DOWN) {
		_velocity.y += 2;
	}

	//	�E�L�[�ŉE�Ɉړ�
	if (key & PAD_INPUT_RIGHT) {
		_velocity.x += 2;
	}

	//	���L�[�ŉE�Ɉړ�
	if (key & PAD_INPUT_LEFT) {
		_velocity.x -= 2;
	}
}

//�@�q�b�g�ʒm
void Player::Hit()
{

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

