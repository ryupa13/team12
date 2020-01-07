#include <DxLib.h>
#include "Enemy.h"
#include "GraphFactory.h"

void Enemy::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\pipo-charachip005.png");
	_size = Vector2(60, 60);
	_radius = 16;
	_position = Vector2(64 * 11, 64);
	_velocity = Vector2(0, 0);

	StateCount = 0;
	HitWallX = false;
	HitWallY = false;
	rnd = 1234;
}

void Enemy::Render()
{
	DrawRectGraph(static_cast<int>(_position.x),
		static_cast<int>(_position.y), 0, 64,
		static_cast<int>(_size.x),
		static_cast<int>(_size.y), _grp, TRUE);
}

void Enemy::Update()
{
	//©—RˆÚ“®
	switch (StateCount)
	{
	case 0://Å‰‚ÌˆÚ“®
		_velocity.x -= 3;
		if (HitWallX == true)
		{
			//‰¡•Ç‚É‚Ô‚Â‚©‚Á‚½‚ç
			StateCount = 1;
		}
		break;
	case 1://•ûŒüŒˆ’è
		//•Ï”‚Éƒ‰ƒ“ƒ_ƒ€‚È’l‚ğŠi”[
		rnd = GetRand(1);
		StateCount = 2;
		break;
	case 2:	//cˆÚ“®
		if (rnd == 0)
		{
			_velocity.y += 3;
		}
		else if (rnd == 1)
		{
			_velocity.y -= 3;
		}

		if (HitWallY == true)
		{
			//c•Ç‚É‚Ô‚Â‚©‚Á‚½‚ç
			StateCount = 3;
		}
		break;
	case 3://•ûŒüŒˆ’è
		//•Ï”‚Éƒ‰ƒ“ƒ_ƒ€‚È’l‚ğŠi”[
		rnd = GetRand(1);
		StateCount = 4;
		break;
	case 4: //‰¡ˆÚ“®
		if (rnd == 0)
		{
			_velocity.x += 3;
		}
		else if (rnd == 1)
		{
			_velocity.x -= 3;
		}

		//c•Ç‚É‚Ô‚Â‚©‚Á‚½‚ç
		if (HitWallX == true)
		{
			StateCount = 1;
		}
		break;

	default:
		break;
	}
}

void Enemy::Release()
{
}

void Enemy::UpdatePosition(bool hitX, bool hitY)
{
	//	X•ûŒü‚ÉÕ“Ë
	if (hitX)
	{
		_velocity.x = 0;
		HitWallX = true;
	}
	else HitWallX = false;

	//	Y•ûŒü‚ÉÕ“Ë
	if (hitY)
	{
		_velocity.y = 0;
		HitWallY = true;
	}
	else HitWallY = false;

	_position += _velocity;
}
