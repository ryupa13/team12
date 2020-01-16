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

	//　ヒット通知
	virtual void Hit() = 0;
	virtual void Hit(GameObject *hitObject) = 0;
	virtual void Hit(bool hitX, bool hitY) = 0;

	//	解放
	virtual void Release() = 0;

	//	※Tipsメンバ関数にconstを付与する事で
	//	その関数内でのメンバ変数の変更を禁止にする
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }
	Vector2 Velocity() const { return _velocity; }
	float Radius() const { return _radius; }
	bool IsDead() const
	{
		if (_state == State::Dead)
			return true;
		return false;
	}
	bool IsClear() const
	{
		if (_state == State::Clear)
			return true;
		return false;
	}

public:
	Vector2 _position;		//	座標
	Vector2 _size;			//	サイズ
	Vector2 _rectSize;
	Vector2 _rectPosition; //切り抜き始める位置
	float _radius;			//	半径
	Vector2 _velocity;
	enum State
	{
		Alive, //生存
		Dead,  //死亡
		Clear
	};
	State _state;
	enum Kind
	{
		Player,
		Enemy,
		Block,
		SmallEnemy,
		Sumi,
	};
	Kind _kind;
<<<<<<< HEAD
	int _isEnemy; //敵同士の衝突判定の同一Enemy識別用
=======
	//int _
>>>>>>> 5a76b1d00273134d99a116fb0b8cc5e9357f4554
};