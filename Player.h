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

	//　解放
	void Release()  override;

	//　ヒット通知
	void Hit() override;
	void Hit(GameObject *hitObject) override;
	void Hit(bool hitX, bool hitY) override;

	//　
	void UpdatePosition(bool hitX, bool hitY);

public:
	//	画像ハンドル
	int _grp;
};