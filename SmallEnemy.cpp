#include "SmallEnemy.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "GameObjectManager.h"

//������
void SmallEnemy::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip010.png");
	_size = Vector2(63, 63);
	_rectPosition = Vector2(0, 32);
	_radius = 32;
	_state = State::Alive;
	_kind = Kind::SmallEnemy;
	_search = SearchState::Free;
	_searchPlayerRadius = 3 * 64;
	_stateCount = 0;
	_chaseCount = 0;
	_hitWallX = false;
	_hitWallY = false;
	_rnd = 1234;
	_inkCount = 100;
}

//�`��
void SmallEnemy::Render()
{
	//�G�l�~�[�̕`��
	Renderer::Instance().DrawGraph(_grp, _position, _rectPosition, _size);
}

//�X�V
void SmallEnemy::Update()
{
	_playerPosition = GameObjectManager::Instance().GetPlayerPosition();
	_inkCount++;

	if (_playerPosition.x - _position.x <= _searchPlayerRadius && _playerPosition.x - _position.x >= -_searchPlayerRadius)
	{
		if (_playerPosition.y - _position.y <= _searchPlayerRadius && _playerPosition.y - _position.y >= -_searchPlayerRadius)
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
void SmallEnemy::Hit()
{
	//_state = State::Dead;
}

void SmallEnemy::Hit(GameObject *hitObject)
{
	if ((*hitObject)._kind == (*hitObject).Player)
	{
		_state = State::Dead;
	}
	if ((*hitObject)._kind == (*hitObject).Sumi)
	{
		if (_inkCount < 100)
			return;

		switch (_stateCount)
		{
		case 0:
			break;
		case 1: //��
			_stateCount = 2;
			_chaseCount = 2;
			break;
		case 2: //��
			_stateCount = 1;
			_chaseCount = 1;
			break;
		case 3: //��
			_stateCount = 4;
			_chaseCount = 4;
			break;
		case 4: //�E
			_stateCount = 3;
			_chaseCount = 3;
			break;
		default:
			break;
		}
		_inkCount = 0;
	}
}

void SmallEnemy::Hit(bool hitX, bool hitY)
{
	UpdatePosition(hitX, hitY);
}

//���
void SmallEnemy::Release()
{

}

void SmallEnemy::UpdateVelocity()
{
	if (_search == SearchState::Chase)
	{
		_playerPosition = GameObjectManager::Instance().GetPlayerPosition();
		_length = _playerPosition - _position;

		switch (_chaseCount)
		{
		case 0: //�������������
			//�c���ǂ����ɓ����邩
			if (_length.x > _length.y) //�c
			{
				//�v���C���[�̏㉺�ǂ��炩�ɋ��邩
				if (_playerPosition.y > _position.y) //��
				{
					_stateCount = 1;
					_chaseCount = 1;
				}
				else //��
				{
					_stateCount = 2;
					_chaseCount = 2;
				}
			}
			else //��
			{
				//�v���C���[�̍��E�ǂ��炩�ɋ��邩
				if (_playerPosition.x > _position.x) //��
				{
					_stateCount = 3;
					_chaseCount = 3;
				}
				else //�E
				{
					_stateCount = 4;
					_chaseCount = 4;
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
							_chaseCount = 4;
						}
					}
				}
				else //�E
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
							_stateCount = 3;
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
				else //�E
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
					_velocity.y = -1;
					_stateCount = 1;
					_chaseCount = 1;

					if (_hitWallY)
					{
						if (_length.x > _length.y)
						{
							_velocity.y = 1;
							_stateCount = 2;
							_stateCount = 2;
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
				else //��
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

void SmallEnemy::UpdatePosition(bool hitX, bool hitY)
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