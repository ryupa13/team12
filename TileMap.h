#pragma once
#include <vector>
#include "Vector2.h"
#include <string>

struct TileHitInfo
{
	bool _hitX;
	bool _hitY;
	int _no;
};

class TileMap
{
public:
	void Start();

	void Render();

	TileHitInfo FindTileHitInfo(const Vector2& pos,
		const Vector2& size, const Vector2& velocity);
private:
	int TileCollision(const Vector2& pos, const Vector2& size, const Vector2& velocity);

	std::vector<int>Split(const std::string& str, char delim = ',');

	std::vector<std::vector<int>> _map;

	int _mapgrp;

	int _tilesize;
};
