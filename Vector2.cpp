#include "Vector2.h"
//	�R���X�g���N�^
Vector2::Vector2() :x(0), y(0) {
}

//	�����t���R���X�g���N�^
Vector2::Vector2(float x, float y) : x(x), y(y) {
}

//	���Z�q�I�[�o�[���[�h�u+�v
Vector2 Vector2::operator + (const Vector2& vec) {

	Vector2 t(this->x + vec.x, this->y + vec.y);

	return t;
}

//	���Z�q�I�[�o�[���[�h�u+=�v
Vector2& Vector2::operator += (const Vector2& vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}


//	���Z�q�I�[�o�[���[�h�u-�v
Vector2 Vector2::operator - (const Vector2& vec) {

	Vector2 t(this->x - vec.x, this->y - vec.y);

	return t;
}

//	���Z�q�I�[�o�[���[�h�u-=�v
Vector2& Vector2::operator -= (const Vector2& vec) {
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2 Vector2::operator*(const float & scale)
{
	Vector2 t(this->x * scale, this->y * scale);

	return t;
}
//	�x�N�g���̓���
float Vector2::Dot(const Vector2& vec)
{
	return (x * vec.x) + (y * vec.y);
}

//	�x�N�g���̊O��
float Vector2::Cross(const Vector2& vec)
{
	return (x * vec.y) - (y * vec.x);
}

//	�x�N�g���̒����擾
float Vector2::Magnitude()
{
	return static_cast<float>(sqrt(x * x + y * y));
}

//	�x�N�g���̐��K��
Vector2 Vector2::Normalized()
{
	return{ x / Magnitude() , y / Magnitude() };
}

void Vector2::Zero()
{
	x = 0; y = 0;
}