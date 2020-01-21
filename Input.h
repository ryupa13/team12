#pragma once
#include "DxLib.h"
#include "Vector2.h"

//Input�N���X
class Input
{
public:
	//�X�V
	static void Update();

	//�L�[�������ꂽ�u�Ԃ��H
	static bool GetKeyTrigger(int keyCode);

	//�L�[��������Ă��邩�H
	static bool GetKeyState(int keyCode);

	//�ړ��ʍX�V
	static void UpdateVelocity();

	//�ړ��ʓ���
	static Vector2 Velocity() { return _velocity; }

private:
	static int _currentKey[256]; //���݂̃L�[�̏��
	static Vector2 _velocity;
};