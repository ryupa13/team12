#include "Enemy.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "GameObjectManager.h"

//������
void Enemy::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip019b.png");
	_size = Vector2(63, 63);
	_rectPosition = Vector2(0, 32);
	_radius = 16;
	_state = State::Alive;
	_kind = Kind::Enemy;
	_search = SearchState::Free;
	_searchPlayerRadius = 160;
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
	Vector2 centerPosition = _position + Vector2(32, 32);
	Vector2 centerPlayerPosition = _playerPosition + Vector2(32, 32);

	if (centerPlayerPosition.x - centerPosition.x <= _searchPlayerRadius && centerPlayerPosition.x - centerPosition.x >= -_searchPlayerRadius)
	{
		if (centerPlayerPosition.y - centerPosition.y <= _searchPlayerRadius && centerPlayerPosition.y - centerPosition.y >= -_searchPlayerRadius)
		{
			_search = SearchState::Chase;
			_speed = 3;
		}
		else
		{
			_search = SearchState::Free;
			_speed = 2;
			_chaseCount = 0;
		}
	}
	else
	{
		_search = SearchState::Free;
		_speed = 2;
		_chaseCount = 0;
	}

	_velocity.Zero();
	UpdateVelocity();
}

//�q�b�g�ʒm
void Enemy::Hit()
{
	_state = State::Dead;
}

void Enemy::Hit(GameObject *hitObject)
{
	if ((*hitObject).Enemy || (*hitObject).SmallEnemy)
		return;
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
		_length = _playerPosition - _position;

		switch (_chaseCount)
		{
		case 0: //��������
			//�c��
			if (_length.x > _length.y) //�c
			{
				//�v���C���[�̏㉺�ǂ��炩�ɋ��邩
				if (_playerPosition.y > _position.y) //��
				{
					_stateCount = 2;
					_chaseCount = 2;
				}
				else //��
				{
					_stateCount = 1;
					_chaseCount = 1;
				}
			}
			else //��
			{
				//�v���C���[�̍��E�ǂ��炩�ɋ��邩
				if (_playerPosition.x > _position.x) //��
				{
					_stateCount = 4;
					_chaseCount = 4;
				}
				else //�E
				{
					_stateCount = 3;
					_chaseCount = 3;
				}
			}
			break;
		case 1: //��
			_velocity.y = -1;
			//�ǂɓ������Ă�����
			if (_hitWallY)
			{
				//�v���C���[�̍��E�ǂ��炩�ɋ��邩
				if (_playerPosition.x > _position.x) //��
				{
					_velocity.x = 1;
					_stateCount = 4;
					_chaseCount = 4;

					if (_hitWallX)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = 1;
							_stateCount = 2;
							_chaseCount = 2;
						}
						else
						{
							_velocity.x = -1;
							_stateCount = 3;
							_chaseCount = 3;
						}
					}
				}
				else //�E
				{
					_velocity.x = -1;
					_stateCount = 3;
					_chaseCount = 3;

					if (_hitWallX)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = 1;
							_stateCount = 2;
							_chaseCount = 2;
						}
						else
						{
							_velocity.x = 1;
							_stateCount = 4;
							_stateCount = 4;
						}
					}
				}
			}
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			break;
		case 2: //��
			_velocity.y = 1;
			//�ǂɓ������Ă�����
			if (_hitWallY)
			{
				//�v���C���[�̍��E�ǂ��炩�ɋ��邩
				if (_playerPosition.x > _position.x) //��
				{
					_velocity.x = 1;
					_stateCount = 4;
					_chaseCount = 4;

					if (_hitWallX)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = -1;
							_stateCount = 1;
							_chaseCount = 1;
						}
						else
						{
							_velocity.x = -1;
							_stateCount = 3;
							_chaseCount = 3;
						}
					}
				}
				else //�E
				{
					_velocity.x = -1;
					_stateCount = 3;
					_chaseCount = 3;

					if (_hitWallX)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = -1;
							_stateCount = 1;
							_chaseCount = 1;
						}
						else
						{
							_velocity.x = 1;
							_stateCount = 4;
							_chaseCount = 4;
						}
					}
				}
			}
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			break;
		case 3: //��
			_velocity.x = -1;
			//�ǂɓ������Ă�����
			if (_hitWallX)
			{
				//�v���C���[�̏㉺�ǂ��炩�ɋ��邩
				if (_playerPosition.y > _position.y) //��
				{
					_velocity.y = 1;
					_stateCount = 2;
					_chaseCount = 2;

					if (_hitWallY)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = -1;
							_stateCount = 1;
							_stateCount = 1;
						}
						else
						{
							_velocity.x = 1;
							_stateCount = 4;
							_chaseCount = 4;
						}
					}
				}
				else //��
				{
					_velocity.y = -1;
					_stateCount = 1;
					_chaseCount = 1;

					if (_hitWallY)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = 1;
							_stateCount = 2;
							_chaseCount = 2;
						}
						else
						{
							_velocity.x = 1;
							_stateCount = 4;
							_chaseCount = 4;
						}
					}
				}
			}
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			break;
		case 4: //�E
			_velocity.x = 1;
			//�ǂɓ������Ă�����
			if (_hitWallX)
			{
				//�v���C���[�̏㉺�ǂ��炩�ɋ��邩
				if (_playerPosition.y > _position.y) //��
				{
					_velocity.y = 1;
					_stateCount = 2;
					_chaseCount = 2;

					if (_hitWallY)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = -1;
							_stateCount = 1;
							_chaseCount = 1;
						}
						else
						{
							_velocity.x = -1;
							_stateCount = 3;
							_chaseCount = 3;
						}
					}
				}
				else //��
				{
					_velocity.y = -1;
					_stateCount = 1;
					_chaseCount = 1;

					if (_hitWallY)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = 1;
							_stateCount = 2;
							_chaseCount = 2;
						}
						else
						{
							_velocity.x = -1;
							_stateCount = 3;
							_chaseCount = 3;
						}
					}
				}
				break;
			}
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
		default:
			break;
		}
	}
	else if (_search == SearchState::Free)
	{
		//���R�ړ�
		switch (_stateCount)
		{
		case 0://�ŏ��̈ړ�
			_velocity.x = 1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallX)
			{
				//���ǂɂԂ�������
				_stateCount = 1;
			}
			break;
		case 1: //��
			_velocity.y = -1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallY)
			{
				_rnd = GetRand(1);
				if (_rnd == 0)
				{
					_stateCount = 3;
				}
				else
				{
					_stateCount = 4;
				}
			}
			break;
		case 2:	//��
			_velocity.y = 1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallY)
			{
				_rnd = GetRand(1);
				if (_rnd == 0)
				{
					_stateCount = 3;
				}
				else
				{
					_stateCount = 4;
				}
			}
			break;
		case 3: //��
			_velocity.x = -1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallX)
			{
				_rnd = GetRand(1);
				if (_rnd == 0)
				{
					_stateCount = 1;
				}
				else
				{
					_stateCount = 2;
				}
			}
			break;
		case 4: //�E
			_velocity.x = 1;
			if (_velocity.Magnitude() != 0)
				_velocity = _velocity.Normalized();
			_velocity = _velocity * _speed;
			if (_hitWallX)
			{
				_rnd = GetRand(1);
				if (_rnd == 0)
				{
					_stateCount = 1;
				}
				else
				{
					_stateCount = 2;
				}
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