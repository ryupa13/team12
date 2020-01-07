#include "TileMap.h"
#include <DxLib.h>
#include "GraphFactory.h"
#include<fstream>
#include<sstream>

TileMap& TileMap::Instance()
{
	static std::unique_ptr<TileMap> instance(new TileMap());

	return *instance;
}

//初期化
void TileMap::Start()
{
	//画像の読み込み
	_mapgrp = GraphFactory::Instance().LoadGraph("img\\maptipsample.png");

#pragma region 配列のマップ
	////タイルマップの情報を作成
//_map = 
//{
//	{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
//	{11, 0, 0, 0, 0, 0, 0, 0,80,11, 0, 0, 0, 0, 0, 0,11, 0, 0,11},
//	{11, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0,65,66, 0, 0,11, 0, 0,11},
//	{11, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0,75,76, 0, 0,11, 0, 0,11},
//	{11, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,11, 0, 0,11},
//	{11, 0, 0,11,11, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11,11,11,11,11,11, 0, 0,11, 0, 0, 0,44,45, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0,54,55, 0,11},
//	{11, 0,70, 0,11, 0, 0,16, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,11},
//	{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
//};//配列のマップ
#pragma endregion

	//マップを読み込む
	std::ifstream ifs("stage\\SampleStage.csv");

	//ファイルの読み込みに成功したら
	if (ifs)
	{
		//文字列を１行ずつ読み込む
		std::string line;
		while (std::getline(ifs, line))
		{
			//読み込んだ文字列をカンマ区切りで分割
			std::vector<int>data = Split(line);

			//マップ情報を格納
			_map.push_back(data);
		}

		int x = 0, y = 0;
		for (auto row : _map)
		{
			x = 0;

			for (auto col : row)
			{
				if (col > 0)
				{

				}
				x++;
			}
			y++;
		}
	}

	//1タイルマップのサイズを設定
	_tilesize = 64;
}

//	描画
void TileMap::Render()
{
	//Xの位置とYの位置
	int x = 0, y = 0;

	//マップ情報を行単位で読み込む
	for (auto row : _map)
	{
		x = 0;

		//マップ情報を取得する
		for (auto col : row)
		{
			//下地の描画
			DrawRectGraph(x*_tilesize, y*_tilesize, 0, 0,
				_tilesize, _tilesize, _mapgrp, TRUE);

			//マップの描画
			auto destX = col % 10;
			auto destY = (col / 10) % 10;

			DrawRectGraph(x*_tilesize, y*_tilesize, destX*_tilesize, destY*_tilesize,
				_tilesize, _tilesize, _mapgrp, TRUE);

			//X方向にタイルマップを1進める
			x++;
		}
		//Y方向にタイルマップを1進める
		y++;
	}
}

//現在位置+サイズ+移動量から現在の衝突状態を取得する
TileHitInfo TileMap::FindTileHitInfo(const Vector2 & pos, const Vector2 & size, const Vector2 & velocity)
{
	//判定を行うキャラの中心座標を取得
	Vector2 center = Vector2((pos.x) + (size.x / 2), (pos.y) + (size.y / 2));

	//X方向の判定
	auto hitx = TileCollision(center, size, Vector2(velocity.x, 0));

	//Y方向の判定
	auto hity = TileCollision(center, size, Vector2(0, velocity.y));

	//衝突結果を格納する
	TileHitInfo info =
	{
		false,
		false,
		0
	};

	//AND演算子を使用し、衝突している場合は1、
	//していない場合は0とする
	info._hitX = (hitx & 1);
	info._hitY = (hity & 1);

	//衝突したオブジェクトの番号を取得する
	info._no = (hitx >> 8) | (hity >> 8);

	return info;
}

//タイルマップの衝突判定を行う
int TileMap::TileCollision(const Vector2 & pos, const Vector2 & size, const Vector2 & velocity)
{
	//左から「左上」「右上」「左下」「右下」になるように配列を格納
	auto sizeX = static_cast<int>(size.x / 2);
	auto sizeY = static_cast<int>(size.y / 2);
	std::vector<int>imageWidth = { -sizeX,sizeX,-sizeX,sizeX };
	std::vector<int>imageHeight = { -sizeY,-sizeY,sizeY,sizeY };

	for (unsigned int index = 0; index < imageWidth.size(); index++)
	{
		//中心座標+各サイズ+移動量で衝突判定を行う
		unsigned int x = static_cast<int>(pos.x + imageWidth[index] + velocity.x) / _tilesize;
		unsigned int y = static_cast<int>(pos.y + imageHeight[index] + velocity.y) / _tilesize;

		//配列の範囲外を参照したら何もしない
		if (y >= _map.size())
		{
			continue;
		}
		if (x >= _map[y].size())
		{
			continue;
		}

		//0出ない場合、何かしらのオブジェクトに衝突した
		if (_map[y][x] > 0)
		{
			//下位8ビットの衝突フラグ、上位８ビットに衝突したオブジェクトを代入
			return 1 | (_map[y][x] << 8);
		}
	}
	//そもそも当たっていない
	return 0;
}

std::vector<int> TileMap::Split(const std::string & str, char delim)
{
	//文字列操作を行うため文字列ストリームを宣言
	std::stringstream iss(str);
	std::string tmp;
	std::vector<int> mapRow;

	//文字列をカンマ区切りで読み込む
	while (std::getline(iss, tmp, delim))
	{
		mapRow.push_back(std::atoi(tmp.c_str()));
	}
	return mapRow;
}
