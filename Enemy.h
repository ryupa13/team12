#pragma once
#include "GameObject.h"
#include "Player.h"

//エネミークラス
class Enemy : public GameObject
{
public:
	//コンストラクタ
	Enemy() {}
	Enemy(Vector2 position) { _position = position; }

	//開始
	void Start() override;

	//描画
	void Render() override;

	//更新
	void Update() override;

	//ヒット通知
	void Hit() override;
	void Hit(bool hitX, bool hitY) override;

	//解放
	void Release() override;

public:
	//画像ハンドル
	int _grp;
	//プレイヤー座標
	Vector2 _playerPosition;
	//プレイヤー感知範囲
	float _searchPlayerRadius;
	//墨感知範囲
	float _searchInkRadius;
	//移動量
	Vector2 _velocity;
};