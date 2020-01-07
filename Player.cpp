#include <DxLib.h>
#include "Player.h"
#include "GraphFactory.h"

//	初期化処理
void Player::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip005.png");
	_size = Vector2(32, 32);
	_radius = 16;
	_position = Vector2(40, 40);
	_velocity = Vector2(0, 0);
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
	//	キー入力を更新
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//	移動量をクリア	
	_velocity = Vector2(0, 0);

	// 上キーで前に進む
	if (key & PAD_INPUT_UP) {
		_velocity.y -= 2;
	}

	//	下キーで後ろに進む
	if (key & PAD_INPUT_DOWN) {
		_velocity.y += 2;
	}

	//	右キーで右に移動
	if (key & PAD_INPUT_RIGHT) {
		_velocity.x += 2;
	}

	//	左キーで右に移動
	if (key & PAD_INPUT_LEFT) {
		_velocity.x -= 2;
	}
}

//	解放
void Player::Release()
{
}

void Player::UpdatePosition(bool hitX, bool hitY)
{
	//	X方向に衝突
	if (hitX)
		_velocity.x = 0;

	//	Y方向に衝突
	if (hitY)
		_velocity.y = 0;

	_position += _velocity;
}

