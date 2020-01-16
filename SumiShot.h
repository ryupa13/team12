#pragma once
#include<list>
#include"Vector2.h"
#include"Sumi.h"
#include"WindowInfo.h"

class SumiShot
{
public:
	~SumiShot();

	void Shot(const Vector2& pos,const Vector2& velocity);

	void Shot(const Vector2& pos, float angle);

	void Update();

	void Render();

public:
	std::list<Sumi*>_shotList;
};

