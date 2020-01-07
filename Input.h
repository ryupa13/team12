#pragma once
#include "DxLib.h"
#include "Vector2.h"

//Inputクラス
class Input
{
public:
	//更新
	static void Update();

	//キーが押された瞬間か？
	static bool GetKeyTrigger(int keyCode);

	//キーが押されているか？
	static bool GetKeyState(int keyCode);

	//移動量更新
	static void UpdateVelocity();

	//移動量入手
	static Vector2 Velocity() { return _velocity; }

private:
	static int _currentKey[256]; //現在のキーの状態
	static Vector2 _velocity;
};