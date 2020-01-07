#include "Input.h"

int Input::_currentKey[256];
Vector2 Input::_velocity;

void Input::Update()
{
	//キーボード
	static char buf[256];
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i])
		{
			if (_currentKey[i] == 0)
				_currentKey[i] = 1;
			else if (_currentKey[i] == 1)
				_currentKey[i] = 2;
		}
		else
			_currentKey[i] = 0;
	}

	//移動量
	UpdateVelocity();
}

bool Input::GetKeyTrigger(int key)
{
	if (_currentKey[key] == 1)
		return true;
	return false;
}

bool Input::GetKeyState(int key)
{
	if (_currentKey[key] == 2)
		return true;
	return false;
}

void Input::UpdateVelocity()
{
	//毎ループ初期化
	_velocity.Zero();

	//上
	if (Input::GetKeyState(KEY_INPUT_UP))
		_velocity.y -= 1;
	//下
	if (Input::GetKeyState(KEY_INPUT_DOWN))
		_velocity.y += 1;
	//左
	if (Input::GetKeyState(KEY_INPUT_LEFT))
		_velocity.x -= 1;
	//右
	if (Input::GetKeyState(KEY_INPUT_RIGHT))
		_velocity.x += 1;

	//正規化
	if (_velocity.Magnitude() != 0)
		_velocity.Normalized();
}