#include <DxLib.h>
#include "Player.h"
#include "GraphFactory.h"

//	初期化処理
void Player::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip005.png");
	_size = Vector2(60, 60);
	_radius = 16;
	_position = Vector2(64, 64);
	_velocity = Vector2(0, 0);


	StateCount = 0;
	HitWallX = false;
	HitWallY = false;
	rnd = 1234;
}

//	描画
void Player::Render()
{
	//	プレイヤーを描画
	DrawRectGraph(static_cast<int>(_position.x),
		static_cast<int>(_position.y), 0, 64,
		static_cast<int>(_size.x),
		static_cast<int>(_size.y), _grp, TRUE);
}

//	更新
void Player::Update()
{

	//	移動量をクリア	
	_velocity = Vector2(0, 0);

#pragma region  キー入力で移動
//	キー入力を更新
int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
// 上キーで前に進む
if (key & PAD_INPUT_UP) {
	_velocity.y -= 3;
}
//	下キーで後ろに進む
if (key & PAD_INPUT_DOWN) {
	_velocity.y += 3;
}
//	右キーで右に移動
if (key & PAD_INPUT_RIGHT) {
	_velocity.x += 3;
}
//	左キーで右に移動
if (key & PAD_INPUT_LEFT) {
	_velocity.x -= 3;
}
#pragma endregion

#pragma region AutoMove
		////自由移動
	//switch (StateCount)
	//{
	//	case 0://最初の移動
	//		_velocity.x += 3;
	//		if (HitWallX == true)
	//		{
	//			//横壁にぶつかったら
	//			StateCount = 1;
	//		}
	//		break;
	//	case 1://方向決定
	//		//変数にランダムな値を格納
	//		rnd = GetRand(1);
	//		StateCount = 2;
	//		break;
	//	case 2:	//縦移動
	//		if (rnd == 0)
	//		{
	//			_velocity.y += 3;
	//		}
	//		else if (rnd == 1)
	//		{
	//			_velocity.y -= 3;
	//		}

	//		if (HitWallY == true)
	//		{
	//			//縦壁にぶつかったら
	//			StateCount = 3;
	//		}
	//		break;
	//	case 3://方向決定
	//		//変数にランダムな値を格納
	//		rnd = GetRand(1);
	//		StateCount = 4;
	//		break;
	//	case 4: //横移動
	//		if (rnd == 0)
	//		{
	//			_velocity.x += 3;
	//		}
	//		else if (rnd == 1)
	//		{
	//			_velocity.x -= 3;
	//		}

	//		//縦壁にぶつかったら
	//		if (HitWallX == true)
	//		{
	//			StateCount = 1;
	//		}
	//		break;

	//default:
	//	break;
	//}
#pragma endregion
}

//	解放
void Player::Release()
{
}

void Player::UpdatePosition(bool hitX, bool hitY)
{
	//	X方向に衝突
	if (hitX)
	{
		_velocity.x = 0;
		HitWallX = true;
	}
	else HitWallX = false;

	//	Y方向に衝突
	if (hitY)
	{
		_velocity.y = 0;
		HitWallY = true;
	}
	else HitWallY = false;

	_position += _velocity;
}

