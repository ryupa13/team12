#include <DxLib.h>
#include "Enemy.h"
#include "GraphFactory.h"

void Enemy::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip005.png");
	_size = Vector2(60, 60);
	_radius = 16;
	_position = Vector2(64 * 11, 64);
	_velocity = Vector2(0, 0);

	StateCount = 0;
	HitWallX = false;
	HitWallY = false;
	rnd = 1234;
}

void Enemy::Render()
{
	DrawRectGraph(static_cast<int>(_position.x),
		static_cast<int>(_position.y), 0, 64,
		static_cast<int>(_size.x),
		static_cast<int>(_size.y), _grp, TRUE);
}

void Enemy::Update()
{
	//���R�ړ�
	switch (StateCount)
	{
	case 0://�ŏ��̈ړ�
		_velocity.x -= 3;
		if (HitWallX == true)
		{
			//���ǂɂԂ�������
			StateCount = 1;
		}
		break;
	case 1://��������
		//�ϐ��Ƀ����_���Ȓl���i�[
		rnd = GetRand(1);
		StateCount = 2;
		break;
	case 2:	//�c�ړ�
		if (rnd == 0)
		{
			_velocity.y += 3;
		}
		else if (rnd == 1)
		{
			_velocity.y -= 3;
		}

		if (HitWallY == true)
		{
			//�c�ǂɂԂ�������
			StateCount = 3;
		}
		break;
	case 3://��������
		//�ϐ��Ƀ����_���Ȓl���i�[
		rnd = GetRand(1);
		StateCount = 4;
		break;
	case 4: //���ړ�
		if (rnd == 0)
		{
			_velocity.x += 3;
		}
		else if (rnd == 1)
		{
			_velocity.x -= 3;
		}

		//�c�ǂɂԂ�������
		if (HitWallX == true)
		{
			StateCount = 1;
		}
		break;

	default:
		break;
	}
}

void Enemy::Release()
{
}

void Enemy::UpdatePosition(bool hitX, bool hitY)
{
	//	X�����ɏՓ�
	if (hitX)
	{
		_velocity.x = 0;
		HitWallX = true;
	}
	else HitWallX = false;

	//	Y�����ɏՓ�
	if (hitY)
	{
		_velocity.y = 0;
		HitWallY = true;
	}
	else HitWallY = false;

	_position += _velocity;
}
