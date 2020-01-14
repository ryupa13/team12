#pragma once
#include "GameObject.h"
#include "Player.h"

//エネミークラス
class SmallEnemy : public GameObject
{
public:
	//コンストラクタ
	SmallEnemy() {}
	SmallEnemy(int isEnemy, Vector2 position) { _isEnemy = isEnemy, _position = position; }

	//開始
	void Start() override;

	//描画
	void Render() override;

	//更新
	void Update() override;

	//ヒット通知
	void Hit() override;
	void Hit(GameObject *hitObject);
	void Hit(bool hitX, bool hitY) override;

	//解放
	void Release() override;

private:
	void UpdateVelocity();
	void UpdatePosition(bool hitX, bool hitY);

public:
	//画像ハンドル
	int _grp;
	//プレイヤー座標
	Vector2 _playerPosition;
	//プレイヤー感知範囲
	float _searchPlayerRadius;
	//墨感知範囲
	float _searchInkRadius;
	//感知状態
	enum SearchState
	{
		Chase,
		Free,
		Ink
	};
	SearchState _search;
	int _stateCount;
	int _chaseCount;
	bool _hitWallX;
	bool _hitWallY;
	int _rnd;
	float _speed;
	Vector2 _length;
};