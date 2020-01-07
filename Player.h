#pragma once
#include "Vector2.h"
#include "GameObject.h"

//	プレイヤークラス
//	※GameObjectクラスを継承する
class Player : public GameObject
{
public:
	//	開始
	//	※override修飾子を使用することで
	//	そのメンバ関数が基底クラスに存在しない場合、エラーを出力する
	void Start() override;

	//	描画
	void Render()  override;

	//	更新
	void Update()  override;

	// 解放
	void Release()  override;

	// 解放
	void UpdatePosition(bool hitX, bool hitY);

	//	速度を取得
	Vector2 Velocity() {
		return _velocity;
	}
public:
	//	画像ハンドル
	int _grp;

	Vector2 _velocity;
};