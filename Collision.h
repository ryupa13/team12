#pragma once
#include "Vector2.h"
#include "GameObject.h"

//	�Փ˔���N���X
class Collision
{
public:
	//	�~�Ή~�̔���
	bool CircleCollision(const GameObject* objectA, const GameObject* objectB);

	//	��`�΋�`�̔���
	bool RectCollision(const GameObject* objectA, const GameObject* objectB);
};