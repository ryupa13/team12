#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include"SumiShot.h"
#include<unordered_map>


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

	

	void UpdateMotion();

	//　ヒット通知
	void Hit() override;
	void Hit(GameObject *hitObject) override;
	void Hit(bool hitX, bool hitY) override;

	//　
	void UpdatePosition(bool hitX, bool hitY);
	enum PDirection
	{
		DOWN, UP, RIGHT, LEFT,
	};
	PDirection pDirection;
private:
	const int AnimationSpeed = 4;
	const int HorizonSheet = 5;
	const int VerticalSheet = 2;

	
public:
	//	画像ハンドル
	int _grp;
	int count;
	int su;
	SumiShot _sumishot;
	std::unordered_map<PDirection, Vector2>_maps{
		{PDirection::DOWN,Vector2 (0,1)},
	{PDirection::UP,Vector2(0,-1)},
	{PDirection::LEFT,Vector2(-1,0)},
	{PDirection::RIGHT,Vector2(1,0)}
	    
	};
	int anime[8];
	int AnimationCount;
	int ImgIndex;
	int animenum;
};