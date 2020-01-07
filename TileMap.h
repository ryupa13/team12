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
private:
	//�O������̃C���X�^���X�����𐧌�
	//�R���X�g���N�^
	TileMap() {}

	//�R�s�[�R���X�g���N�^
	TileMap(const TileMap&) {}

	//�R�s�[������Z�q
	TileMap& operator= (const TileMap&) {}

public:
	//�C���X�^���X�̎擾
	static TileMap& Instance();

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
