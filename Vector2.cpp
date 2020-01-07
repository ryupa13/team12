#include "Vector2.h"
//	コンストラクタ
Vector2::Vector2() :x(0), y(0) {
}

//	引数付きコンストラクタ
Vector2::Vector2(float x, float y) : x(x), y(y) {
}

//	演算子オーバーロード「+」
Vector2 Vector2::operator + (const Vector2& vec) {

	Vector2 t(this->x + vec.x, this->y + vec.y);

	return t;
}

//	演算子オーバーロード「+=」
Vector2& Vector2::operator += (const Vector2& vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}


//	演算子オーバーロード「-」
Vector2 Vector2::operator - (const Vector2& vec) {

	Vector2 t(this->x - vec.x, this->y - vec.y);

	return t;
}

//	演算子オーバーロード「-=」
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
//	ベクトルの内積
float Vector2::Dot(const Vector2& vec)
{
	return (x * vec.x) + (y * vec.y);
}

//	ベクトルの外積
float Vector2::Cross(const Vector2& vec)
{
	return (x * vec.y) - (y * vec.x);
}

//	ベクトルの長さ取得
float Vector2::Magnitude()
{
	return static_cast<float>(sqrt(x * x + y * y));
}

//	ベクトルの正規化
Vector2 Vector2::Normalized()
{
	return{ x / Magnitude() , y / Magnitude() };
}

void Vector2::Zero()
{
	x = 0; y = 0;
}