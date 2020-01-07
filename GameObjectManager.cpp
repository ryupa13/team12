#include "DxLib.h"
#include <memory>
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

//�f�X�g���N�^
GameObjectManager::~GameObjectManager()
{
	//�������
	for (auto p : _players)
	{
		delete p;
	}
	for (auto e : _enemys)
	{
		delete e;
	}
	for (auto b : _blocks)
	{
		delete b;
	}
}

//�N���X�̃C���X�^���X���擾
GameObjectManager & GameObjectManager::Instance()
{
	static std::unique_ptr<GameObjectManager> instance(new GameObjectManager);

	return *instance;
}

//������
void GameObjectManager::Start()
{
	for (auto p = _players.begin(); p != _players.end();)
	{
		p = _players.erase(p);
		continue;

		++p;
	}
	for (auto e = _enemys.begin(); e != _enemys.end();)
	{
		e = _enemys.erase(e);
		continue;

		++e;
	}
	for (auto b = _blocks.begin(); b != _blocks.end();)
	{
		b = _blocks.erase(b);
		continue;

		++b;
	}
}

//�X�V
void GameObjectManager::Update()
{
	for (auto newObject : _addNewGameObjects)
	{
		newObject->Start();
		if (newObject->_kind == 0)
		{
			_players.push_back(newObject);
		}
		if (newObject->_kind == 1)
		{
			_enemys.push_back(newObject);
		}
	}

	if (!_addNewGameObjects.empty())
	{
		for (auto a = _addNewGameObjects.begin(); a != _addNewGameObjects.end();)
		{
			a = _addNewGameObjects.erase(a);
			continue;

			++a;
		}
	}

	for (auto p : _players)
	{
		p->Update();
	}
	for (auto e : _enemys)
	{
		e->Update();
	}

	HitToCharacters();

	RemoveDeadGameObjects();
}

//�`��
void GameObjectManager::Render()
{
	for (auto p : _players)
	{
		p->Render();
	}
	for (auto e : _enemys)
	{
		e->Render();
	}
}

//�ǉ�
void GameObjectManager::Add(GameObject* gameObject)
{
	if (gameObject == nullptr)
		return;

	//�ǉ����X�g�ɃI�u�W�F�N�g��ǉ�
	_addNewGameObjects.push_back(gameObject);
}

//�v���C���[�ƃG�l�~�[�̓����蔻��
void GameObjectManager::HitToCharacters()
{
	//�v���C���[�ŌJ��Ԃ�
	for (auto p = _players.begin(); p != _players.end();)
	{
		//�G�l�~�[�ŌJ��Ԃ�
		for (auto e = _enemys.begin(); e != _enemys.end();)
		{
			//�ǂ��炩������ł��玟��
			if ((*p)->IsDead() || (*e)->IsDead())
				continue;

			//�v���C���[�ƃG�l�~�[���Փ˂��Ă��邩
			if (_collision.CircleCollision(*p, *e))
			{
				//�݂��Ƀq�b�g�ʒm
				(*p)->Hit();
				(*e)->Hit();
			}
			++e;
		}
		++p;
	}
}

//�u���b�N�Ƃ̓����蔻��
void GameObjectManager::HitToBlocks()
{
	//�u���b�N�ŌJ��Ԃ�
	for (auto b = _blocks.begin(); b != _blocks.end();)
	{
		//�v���C���[�ŌJ��Ԃ�
		for (auto p = _players.begin(); p != _players.end();)
		{
			//�ǂ��炩������ł��玟��
			if ((*b)->IsDead() || (*p)->IsDead())
				continue;

			//�u���b�N�ƃv���C���[���Փ˂��Ă��邩
			if (_collision.RectCollision(*b, *p))
			{
				//�v���C���[�Ƀq�b�g�ʒm
				(*p)->Hit();
			}
			++p;
		}
		//�G�l�~�[�ŌJ��Ԃ�
		for (auto e = _enemys.begin(); e != _enemys.end();)
		{
			//�ǂ��炩������ł��玟��
			if ((*b)->IsDead() || (*e)->IsDead())
				continue;

			//�u���b�N�ƃG�l�~�[���Փ˂��Ă��邩
			if (_collision.RectCollision(*b, *e))
			{
				//�G�l�~�[�Ƀq�b�g�ʒm
				(*e)->Hit();
			}
			++e;
		}
		++b;
	}
}

//�G�l�~�[���m�̓����蔻��
void GameObjectManager::HitToEnemys()
{
	//�G�l�~�[�ŌJ��Ԃ�
	for (auto enemy = _enemys.begin(); enemy != _enemys.end();)
	{
		//�G�l�~�[�ŌJ��Ԃ�
		for (auto e = _enemys.begin(); e != _enemys.end();)
		{
			//�����G�l�~�[�Ȃ玟��
			if (enemy == e)
				continue;

			//�ǂ��炩������ł��玟��
			if ((*enemy)->IsDead() || (*e)->IsDead())
				continue;

			//�G�l�~�[���m���Փ˂��Ă��邩
			if (_collision.RectCollision(*enemy, *e))
			{
				//���݂��Ƀq�b�g�ʒm
				(*enemy)->Hit();
				(*e)->Hit();
			}
			++e;
		}
		++enemy;
	}
}

//���S�Q�[���I�u�W�F�N�g�̍폜
void GameObjectManager::RemoveDeadGameObjects()
{
	//����ł����烊�X�g����폜
	for (auto p = _players.begin(); p != _players.end();)
	{
		if ((*p)->IsDead())
		{
			p = _players.erase(p);
			continue;
		}
		++p;
	}
	for (auto e = _enemys.begin(); e != _enemys.end();)
	{
		if ((*e)->IsDead())
		{
			e = _enemys.erase(e);
			continue;
		}
		++e;
	}
	for (auto b = _blocks.begin(); b != _blocks.end();)
	{
		if ((*b)->IsDead())
		{
			b = _blocks.erase(b);
			continue;
		}
		++b;
	}
}

void GameObjectManager::TileMapCollision(bool hitX, bool hitY)
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
			return p->Hit(hitX, hitY);
	}
}

Vector2 GameObjectManager::GetPlayerPosition()
{
	for (auto p : _players)
	{
		if (p->_kind == 0)
			return p->Position();
	}
	return Vector2(0, 0);
}

Vector2 GameObjectManager::GetPlayerSize()
{
	for (auto p : _players)
	{
		if (p->_kind == 0)
			return p->Size();
	}
	return Vector2(0, 0);
}

Vector2 GameObjectManager::GetPlayerVelocity()
{
	for (auto p : _players)
	{
		if (p->_kind == 0)
			return p->Velocity();
	}
	return Vector2(0, 0);
}