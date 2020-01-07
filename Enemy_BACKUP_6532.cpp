<<<<<<< HEAD
#include "Enemy.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "GameObjectManager.h"

//������
void Enemy::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip019b.png");
	_size = Vector2(32, 32);
	_rectPosition = Vector2(0, 32);
	_radius = 16;
	_state = State::Alive;
	_kind = Kind::Enemy;
	_searchPlayerRadius = 320;
}

//�`��
void Enemy::Render()
{
	//�G�l�~�[�̕`��
	Renderer::Instance().DrawGraph(_grp, _position, _rectPosition, _size);
}

//�X�V
void Enemy::Update()
{
	_playerPosition = GameObjectManager::Instance().GetPlayerPosition();

	if (_playerPosition.x - _position.x <= _searchPlayerRadius && _playerPosition.x - _position.x >= -_searchPlayerRadius)
	{
		if (_playerPosition.y - _position.y <= _searchPlayerRadius && _playerPosition.y - _position.y >= -_searchPlayerRadius)
		{
			_velocity = _playerPosition - _position;
			_velocity = _velocity.Normalized();
		}
		else
		{
			_velocity.Zero();
		}
	}
	else
	{
		_velocity.Zero();
	}

	_position += _velocity * 3;
}

//�q�b�g�ʒm
void Enemy::Hit()
{
	_state = State::Dead;
}

void Enemy::Hit(bool hitX, bool hitY)
{

}

//���
void Enemy::Release()
{

}
=======
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
>>>>>>> 35f0a1e7f9cafb2d0df6fb88f3b918d60a96626e
