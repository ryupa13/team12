#include "DxLib.h"
#include <memory>
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include"Sumi.h"

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
	for (auto s : _sumis)
	{
		delete s;
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
	for (auto s = _sumis.begin(); s != _sumis.end();)
	{
		s = _sumis.erase(s);
		continue;
		++s;
	}
}

//�X�V
void GameObjectManager::Update()
{
	for (auto newObject : _addNewGameObjects)
	{
		newObject->Start();
		if (newObject->_kind == newObject->Player)
		{
			_players.push_back(newObject);
		}
		if (newObject->_kind == newObject->Enemy || newObject->_kind == newObject->SmallEnemy)
		{
			_enemys.push_back(newObject);
		}
		if (newObject->_kind == newObject->Block)
		{
			_blocks.push_back(newObject);
		}
		if (newObject->_kind == newObject->Sumi)
		{
			_sumis.push_back(newObject);
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
	HitToEnemys();
	HitToSumis();
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
	for (auto s : _sumis)
	{
		s->Render();
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
	for (auto p = _players.begin(); p != _players.end(); ++p)
	{
		//�G�l�~�[�ŌJ��Ԃ�
		for (auto e = _enemys.begin(); e != _enemys.end(); ++e)
		{
			//�ǂ��炩������ł��玟��
			if ((*p)->IsDead() || (*e)->IsDead())
				continue;

			//�v���C���[�ƃG�l�~�[���Փ˂��Ă��邩
			if (_collision.CircleCollision(*p, *e))
			{
				//�݂��Ƀq�b�g�ʒm
				(*p)->Hit(*e);
				(*e)->Hit(*p);
			}
		}
	}
}

//�u���b�N�Ƃ̓����蔻��
void GameObjectManager::HitToBlocks()
{
	//�u���b�N�ŌJ��Ԃ�
	for (auto b = _blocks.begin(); b != _blocks.end(); ++b)
	{
		//�v���C���[�ŌJ��Ԃ�
		for (auto p = _players.begin(); p != _players.end(); ++p)
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
		}
		//�G�l�~�[�ŌJ��Ԃ�
		for (auto e = _enemys.begin(); e != _enemys.end(); ++e)
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
		}
	}
}

//�n�̓����蔻��
void GameObjectManager::HitToSumis()
{
	//�n�ŌJ��Ԃ�
	for (auto s = _sumis.begin(); s != _sumis.end();++s)
	{
		//�v���C���[�ŌJ��Ԃ�
		for (auto p = _players.begin(); p != _players.end();++p)
		{
			//�����G�l�~�[�Ȃ玟��
			if ((*p) == (*s))
				continue;

			//�ǂ��炩������ł��玟��
			if ((*p)->IsDead() || (*s)->IsDead())
				continue;

				//�v���C���[���m���Փ˂��Ă��邩
			if (_collision.CircleCollision(*p, *s))
			{
				//���݂��Ƀq�b�g�ʒm
				(*p)->Hit(*s);
				(*s)->Hit(*p);
			}
		}

		for (auto e = _enemys.begin(); e != _enemys.end();++e)
		{
			if ((*s)->IsDead() || (*e)->IsDead())
				continue;
			
			if (_collision.CircleCollision(*s, *e))
			{
				(*e)->Hit(*s);
				(*s)->Hit(*e);
			}
		}
	}
}

//�G�l�~�[���m�̓����蔻��
void GameObjectManager::HitToEnemys()
{
	//�G�l�~�[�ŌJ��Ԃ�
	for (auto enemy : _enemys)
	{
		//�G�l�~�[�ŌJ��Ԃ�
		for (auto e : _enemys)
		{
			//�����G�l�~�[�Ȃ玟��
			if (enemy->_isEnemy == e->_isEnemy)
				continue;

			//�ǂ��炩������ł��玟��
			if (enemy->IsDead() || e->IsDead())
				continue;

			//�G�l�~�[���m���Փ˂��Ă��邩
			if (_collision.RectCollision(enemy, e))
			{
				//���݂��Ƀq�b�g�ʒm
				enemy->Hit(e);
				e->Hit(enemy);
			}
		}
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

	for (auto s = _sumis.begin();s != _sumis.end(); ++s)
	{
		if ((*s)->IsDead())
		{
			_sumis.erase(s);
			break;
		}
	}
}

void GameObjectManager::TileMapCollision()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
		{
			auto pInfo = TileMap::Instance().FindTileHitInfo((*p).Position(), (*p).Size(), (*p).Velocity());
			p->Hit(pInfo._hitX, pInfo._hitY);

			if (pInfo._hitX == 1 || pInfo._hitY == 1)
			{
				if (pInfo._no == 80)
				{
					p->_state = p->Clear;
				}
			}
		}
	}
	for (auto e : _enemys)
	{
		if (e->_kind == e->Enemy || e->_kind == e->SmallEnemy)
		{
			auto eInfo = TileMap::Instance().FindTileHitInfo((*e).Position(), (*e).Size(), (*e).Velocity());
			e->Hit(eInfo._hitX, eInfo._hitY);
		}
	}
}

Vector2 GameObjectManager::GetPlayerPosition()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
			return p->Position();
	}
	return Vector2(0, 0);
}

Vector2 GameObjectManager::GetPlayerSize()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
			return p->Size();
	}
	return Vector2(0, 0);
}

Vector2 GameObjectManager::GetPlayerVelocity()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
			return p->Velocity();
	}
	return Vector2(0, 0);
}

bool GameObjectManager::GetClearFlag()
{
	for (auto p : _players)
	{
		if (p->_kind == p->Player)
		{
			return p->IsClear();
		}
		return false;
	}
}