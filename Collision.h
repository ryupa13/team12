#pragma once
#include "Vector2.h"
#include "GameObject.h"

//	衝突判定クラス
class Collision
{
public:
	//	円対円の判定
	bool CircleCollision(const GameObject* objectA, const GameObject* objectB);

	//	矩形対矩形の判定
	bool RectCollision(const GameObject* objectA, const GameObject* objectB);
};