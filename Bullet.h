#pragma once
#include "Vector2.h"
#include<DxLib.h>

class Bullet
{
public:
	Bullet(Vector2 pos);

	~Bullet();

	void Start();

	void Render();

	void Update();

	Vector2 GetPosition()
	{
		return _position;
	}

	Vector2 GetSize()
	{
		return _size;
	}

private:
	const int AnimationSpeed = 4;
	const int HorizonSheet = 5;
	const int VerticalSheet = 4;
	Vector2 _position;
	Vector2 _size;
	Vector2 _offset;
	Vector2 _velocity;
	int grp;
	int _animFrameCount;
};