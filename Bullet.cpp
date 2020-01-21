#include "Bullet.h"
#include "GraphFactory.h"

Bullet::Bullet(Vector2 pos)
	:_position(pos),
	_size(Vector2(32,32))
{
	_velocity = Vector2(1, 0);
}

Bullet::~Bullet()
{
	GraphFactory::Instance().EraseGraph("img\\pipo-mapeffect011j.png");
}

void Bullet::Start()
{
	grp = GraphFactory::Instance().LoadGraph("img\\pipo-mapeffect011j.png");
	_animFrameCount = 0;
}

void Bullet::Render()
{
	//	���]�t���O��TRUE�ɂ��Ă���͉̂摜�̌����̊֌W��
	DrawRectGraph(static_cast<int>(_position.x),
		static_cast<int>(_position.y), _offset.x, _offset.y,
		static_cast<int>(_size.x),
		static_cast<int>(_size.y), grp, TRUE, TRUE);
}

void Bullet::Update()
{
	_animFrameCount++;

	auto sheetNo = _animFrameCount / AnimationSpeed;
	_offset.x = (sheetNo % HorizonSheet)* _size.x;
	_offset.y = ((sheetNo / HorizonSheet) % VerticalSheet)* _size.y;

	//�ړ��X�V
	_position += _velocity;
}
