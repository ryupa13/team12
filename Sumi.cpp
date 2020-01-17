#define _USE_MATH_DEFINES
#include "Sumi.h"
#include"GraphFactory.h"
#include<cmath>
#include"Renderer.h"
#include"Input.h"



Sumi::Sumi(Vector2 pos,Vector2 velocity)
{
	_position = pos;
	_velocity = velocity;
	_size = Vector2(64, 64);
	//_position.x += _size.x;
	_position =_position + velocity * _size;
}

Sumi::Sumi(Vector2 pos, float angle)
{
	float velocity = 2.0f;

	auto x = cos((M_PI / 180)*angle)*velocity;
	auto y = sin((M_PI / 180)*angle)*velocity;

	_velocity = Vector2(x, y);
}

void Sumi::Start()
{
	_grp = GraphFactory::Instance().LoadGraph("img\\tama.png");
	_animFrameCount = 0;
	_radius = 32;
	_state = State::Alive;
	_kind = Kind::Sumi;
}

void Sumi::Render()
{
	//	ƒvƒŒƒCƒ„[‚ğ•`‰æ
	Renderer::Instance().DrawGraph(_grp, _position, _rectPosition, _size);
}

void Sumi::Update()
{
	_animFrameCount++;

	auto sheetNo = _animFrameCount / AnimationSpeed;
	_offset.x = (sheetNo % HorizonSheet) * _size.x;
	_offset.y = ((sheetNo / HorizonSheet) % VerticalSheet) * _size.y;

	//_position += _velocity;
}

void Sumi::Release()
{
}

void Sumi::Hit()
{
	/*if (count >= 1)
	{*/
	///_state = State::Dead;
	//}
}

void Sumi::Hit(bool hitX, bool hitY)
{
	UpdatePosition(hitX, hitY);
	count++;
}

void Sumi::Hit(GameObject * hitObject)
{
	if ((*hitObject)._kind == (*hitObject).Enemy)
	{
		_state = State::Dead;
	}
}

void Sumi::UpdatePosition(bool hitX, bool hitY)
{
	//	X•ûŒü‚ÉÕ“Ë
	if (hitX)
		_velocity.x = 0;

	//	Y•ûŒü‚ÉÕ“Ë
	if (hitY)
		_velocity.y = 0;

	_position += _velocity;
}
