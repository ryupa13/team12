#include "SmallEnemy.h"
#include "GraphFactory.h"
#include "Renderer.h"
#include "GameObjectManager.h"

//������
void SmallEnemy::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip019b.png");
	_size = Vector2(32, 32);
	_rectPosition = Vector2(0, 32);
	_radius = 16;
	_state = State::Alive;
	_kind = Kind::Enemy;
	_searchPlayerRadius = 80;
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

	_position += _velocity * -3;
}

//�q�b�g�ʒm
void SmallEnemy::Hit()
{
	_state = State::Dead;
}

void SmallEnemy::Hit(bool hitX, bool hitY)
{

}

//���
void SmallEnemy::Release()
{

}