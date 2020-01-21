#pragma once
#include <list>
#include "Vector2.h"
#include "Bullet.h"
#include "WindowInfo.h"

class PlayerShot
{
public:
	~PlayerShot();

	void Shot(const Vector2& pos);

	void Update();

	void Render();
public:
	//�e�N���X�̃��X�g�i������ł����₷���Ƃ��ł���j
	std::list<Bullet*> _shotList;
};