#pragma once
#include "Vector2.h"

//	ゲームオブジェクトクラス
class GameObject
{
public:
	//	コンストラクタ
	GameObject() : _position(0, 0), _size(0, 0) {}

	//	開始
	virtual void Start() = 0;

	//	描画
	virtual void Render() = 0;

	//	更新
	virtual void Update() = 0;

	//	解放
	virtual void Release() = 0;

	//	※Tipsメンバ関数にconstを付与する事で
	//	その関数内でのメンバ変数の変更を禁止にする
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }
	float Radius() const { return _radius; }

public:
	Vector2 _position;		//	座標
	Vector2 _size;			//	サイズ
	float _radius;			//	半径
};