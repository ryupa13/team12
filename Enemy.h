#pragma once
#include "Vector2.h"
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	void Start() override;

	void Render() override;

	void Update() override;

	void Release() override;

	void UpdatePosition(bool hitX, bool hitY);

	Vector2 Velocity() { return _velocity; }

public:
	int _grp;

	Vector2 _velocity;

	int StateCount;
	bool HitWallX;
	bool HitWallY;
	int rnd;
};