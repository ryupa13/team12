#include <DxLib.h>
#include "Player.h"
#include "GraphFactory.h"

//	����������
void Player::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip005.png");
	_size = Vector2(32, 32);
	_radius = 16;
	_position = Vector2(40, 40);
	_velocity = Vector2(0, 0);
}

//	�`��
void Player::Render()
{
	//	�v���C���[��`��
	DrawRectGraph(static_cast<int>(_position.x),
		static_cast<int>(_position.y), 0, 64,
		static_cast<int>(_size.x),
		static_cast<int>(_size.y), _grp, TRUE);
}

//	�X�V
void Player::Update()
{
	//	�L�[���͂��X�V
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//	�ړ��ʂ��N���A	
	_velocity = Vector2(0, 0);

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

