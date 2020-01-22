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
	_sumiImage = GraphFactory::Instance().LoadGraph("img\\sumi.png");
	_bombImage = GraphFactory::Instance().LoadGraph("img\\bom.png");

	_desImage = GraphFactory::Instance().LoadGraph("img\\bakuhatu.png");

	_rectPosition = Vector2(0, 0);

	_animFrameCount = 0;
	_radius = 32;
	_state = State::Alive;
	_kind = Kind::Sumi;
	count = 0;
	descount = 0;
	sumicount = 0;

}

void Sumi::Render()
{
	if (_state == State::Alive)
	{
		//	ÉvÉåÉCÉÑÅ[Çï`âÊ

		Renderer::Instance().DrawGraph(static_cast<int>(_position.x),
			static_cast<int>(_position.y),_offset.x,_offset.y,
			static_cast<int>(_size.x),
			static_cast<int>(_size.y),_sumiImage,TRUE,TRUE,TRUE);

	}
	if (_state == State::Bomb)
	{
		Renderer::Instance().DrawGraph(static_cast<int>(_position.x),
			static_cast<int>(_position.y), _offset.x, _offset.y,
			static_cast<int>(_size.x),
			static_cast<int>(_size.y), _bombImage, TRUE, TRUE, TRUE);
	}

	if (_state == State::Dying)
	{
		Renderer::Instance().DrawGraph(static_cast<int>(_position.x),
			static_cast<int>(_position.y), _offset.x, _offset.y,
			static_cast<int>(_size.x),
			static_cast<int>(_size.y), _desImage, TRUE, TRUE, TRUE);
	}
}

void Sumi::Update()
{
	_animFrameCount++;

	auto sheetNo = _animFrameCount / AnimationSpeed;
	_offset.x = (sheetNo % HorizonSheet) * _size.x;
	_offset.y = ((sheetNo / HorizonSheet) % VerticalSheet) * _size.y;
	
	if (_state == State::Alive)
	{
		sumicount++;
	}

	if (_state == State::Dying)
	{
		descount++;
		if (descount == 10)
		{
			descount = 0;
			_state = State::Dead;
			
		}
	}

	

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
	if ((*hitObject)._kind == (*hitObject).Player && Input::GetKeyTrigger(KEY_INPUT_X))
	{
		_state = State::Bomb;
	}
	if ((*hitObject)._kind == (*hitObject).Enemy || (*hitObject)._state == State::Bomb && (*hitObject)._kind == (*hitObject).Enemy)
	{
		_state = State::Dying;
	}
	
}

void Sumi::UpdatePosition(bool hitX, bool hitY)
{
	//	Xï˚å¸Ç…è’ìÀ
	if (hitX)
		_velocity.x = 0;

	//	Yï˚å¸Ç…è’ìÀ
	if (hitY)
		_velocity.y = 0;

	_position += _velocity;
}
