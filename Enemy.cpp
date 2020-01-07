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
	_search = SearchState::Free;
	_searchPlayerRadius = 320;
	_stateCount = 0;
	_hitWallX = false;
	_hitWallY = false;
	_rnd = 1234;
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
			_search = SearchState::Chase;
		}
		else
		{
			_search = SearchState::Free;
		}
	}
	else
	{
		_search = SearchState::Free;
	}

	_velocity.Zero();
	UpdateVelocity();
}

//�q�b�g�ʒm
void Enemy::Hit()
{
	_state = State::Dead;
}

void Enemy::Hit(bool hitX, bool hitY)
{
	UpdatePosition(hitX, hitY);
}

//���
void Enemy::Release()
{

}

void Enemy::UpdateVelocity()
{
	if (_search == SearchState::Chase)
	{
		_playerPosition = GameObjectManager::Instance().GetPlayerPosition();
		_velocity = _playerPosition - _position;
		_velocity = _velocity.Normalized();
		_velocity = _velocity * 3;
	}
	else if (_search == SearchState::Free)
	{
		//���R�ړ�
		switch (_stateCount)
		{
		case 0://�ŏ��̈ړ�
			_velocity.x -= 1;
			if (_hitWallX == true)
			{
				//���ǂɂԂ�������
				_stateCount = 1;
			}
			break;
		case 1://��������
			//�ϐ��Ƀ����_���Ȓl���i�[
			_rnd = GetRand(1);
			_stateCount = 2;
			break;
		case 2:	//�c�ړ�
			if (_rnd == 0)
			{
				_velocity.y += 1;
			}
			else if (_rnd == 1)
			{
				_velocity.y -= 1;
			}

			if (_hitWallY == true)
			{
				//�c�ǂɂԂ�������
				_stateCount = 3;
			}
			break;
		case 3://��������
			//�ϐ��Ƀ����_���Ȓl���i�[
			_rnd = GetRand(1);
			_stateCount = 4;
			break;
		case 4: //���ړ�
			if (_rnd == 0)
			{
				_velocity.x += 1;
			}
			else if (_rnd == 1)
			{
				_velocity.x -= 1;
			}

			//�c�ǂɂԂ�������
			if (_hitWallX == true)
			{
				_stateCount = 1;
			}
			break;

		default:
			break;
		}
	}
}

void Enemy::UpdatePosition(bool hitX, bool hitY)
{
	//	X�����ɏՓ�
	if (hitX)
	{
		_velocity.x = 0;
		_hitWallX = true;
	}
	else _hitWallX = false;

	//	Y�����ɏՓ�
	if (hitY)
	{
		_velocity.y = 0;
		_hitWallY = true;
	}
	else _hitWallY = false;

	_position += _velocity;
}