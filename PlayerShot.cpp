#include "PlayerShot.h"

PlayerShot::~PlayerShot()
{
	//���X�g�̒��g���폜
	for (auto shot : _shotList)
	{
		delete shot;
	}
}

void PlayerShot::Shot(const Vector2 & pos)
{
	//���������ɒe�𐶐�����
	Bullet* shot = new Bullet(pos);

	//�������ꂽ�e�̏�����
	shot->Start();

	//�����E���������ꂽ�e���A���X�g�Ɋi�[����B
	_shotList.push_back(shot);
}

void PlayerShot::Update()
{
	//�C�e���[�^���g���A���X�g�̍ŏ�����Ō�܂ł��ꊇ�Ǘ�
	for (auto it = _shotList.begin(); it != _shotList.end();)
	{
		(*it)->Update();

		if ((*it)->GetPosition().x > WindowInfo::WindowWidth)
		{
			delete *it;
			it = _shotList.erase(it);
			continue;
		}
		++it;
	}
}

void PlayerShot::Render()
{
	for (auto shot : _shotList)
	{
		shot->Render();
	}
}
