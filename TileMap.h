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
	//外部からのインスタンス生成を制限
	//コンストラクタ
	TileMap() {}

	//コピーコンストラクタ
	TileMap(const TileMap&) {}

	//コピー代入演算子
	TileMap& operator= (const TileMap&) {}

public:
	//インスタンスの取得
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
