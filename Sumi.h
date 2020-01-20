#pragma once
#include"Vector2.h"
#include"DxLib.h"
#include"GameObject.h"
#include"TileMap.h"

class Sumi : public GameObject
{
public:
	Sumi(Vector2 pos,Vector2 velocity);

	Sumi(Vector2 pos, float angle);




	void Start() override;

	void Render()override;

	void Update() override;

	void Release() override;

	//　ヒット通知
	void Hit() override;
	void Hit(bool hitX, bool hitY) override;
	void Hit(GameObject *hitObject) override;

	void UpdatePosition(bool hitX, bool hitY);

private:
	const int AnimationSpeed = 4;
	const int HorizonSheet = 5;
	const int VerticalSheet = 4;

	Vector2 _offset;
	Vector2 _velocity;
	int _sumiImage;
	int _bombImage;
	int _desImage;
	int _animFrameCount;
	int count;
	int descount;
};