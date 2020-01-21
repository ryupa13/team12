#pragma once
#include "GameObject.h"
#include "Player.h"

//ブロッククラス
class Block : public GameObject
{
public:
	//コンストラクタ
	Block() {}
	Block(Vector2 position) { _position = position; }

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
};