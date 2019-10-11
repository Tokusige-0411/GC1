#include "Vector2.h"
#include <_DebugConout.h>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(int x, int y)
{
	Vector2::x = x;
	Vector2::y = y;
}

Vector2::~Vector2()
{
}

// 代入演算子
Vector2 & Vector2::operator=(const Vector2 & vec)
{
	x = vec.x;
	y = vec.y;

	// ｲﾝｽﾀﾝｽされてないのでﾎﾟｲﾝﾀを返す(自分自身を返す)
	// 参照返しは実体で返す(thisはポインタなので*をつけて実体を返す)
	// thisはそこの関数のﾎﾟｲﾝﾀ
	return *this;
}

int & Vector2::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

bool Vector2::operator==(const Vector2 & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

bool Vector2::operator!=(const Vector2 & vec) const
{
	// return ((this->x != vec.x) || (this->y != vec.y));
	return !((this->x == vec.x) && (this->y == vec.y));
}

bool Vector2::operator>(const Vector2 & vec) const
{
	return (this->x > vec.x) && (this->y > vec.y);
}

bool Vector2::operator>=(const Vector2 & vec) const
{
	return (this->x >= vec.x) && (this->y >= vec.y);
}

// 単項演算子
Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

Vector2 & Vector2::operator*=(int k)
{
	x *= k;
	y *= k;

	return *this;
}

Vector2 & Vector2::operator/=(int k)
{
	x /= k;
	y /= k;

	return *this;
}

Vector2 Vector2::operator+()const
{
	return *this;
}

Vector2 Vector2::operator-()const
{
	return Vector2(-this->x, -this->y);
}

Vector2 operator+(const Vector2 & u, const int k)
{
	Vector2 vec;
	vec = { u.x + k, u.y + k };
	return vec;
}

Vector2 operator-(const Vector2 & u, const int k)
{
	Vector2 vec;
	vec = { u.x - k, u.y - k };
	return vec;
}

Vector2 operator+(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec = { u.x + v.x, u.y + v.y };
	return vec;
}

Vector2 operator-(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec = { u.x - v.x, u.y - v.y };
	return vec;
}

Vector2 operator*(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec = { u.x * v.x, u.y * v.y };
	return vec;
}

Vector2 operator/(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec = { u.x / v.x, u.y / v.y };
	return vec;
}

Vector2 operator%(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec = { u.x % v.x, u.y % v.y };
	return vec;
}

Vector2 operator%(const Vector2 & u, const int k)
{
	Vector2 vec;
	vec = { u.x % k, u.y % k };
	return vec;
}

Vector2 operator*(const Vector2 & u, const int k)
{
	Vector2 vec;
	vec = { u.x * k, u.y * k };
	return vec;
}

Vector2 operator*(const int k, const Vector2 & u)
{
	Vector2 vec;
	vec = { k * u.x, k * u.y };
	return vec;
}

Vector2 operator/(const Vector2 & u, const int k)
{
	Vector2 vec;
	vec = { k / u.x, k / u.y };
	return vec;
}
