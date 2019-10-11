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

// ������Z�q
Vector2 & Vector2::operator=(const Vector2 & vec)
{
	x = vec.x;
	y = vec.y;

	// �ݽ�ݽ����ĂȂ��̂��߲����Ԃ�(�������g��Ԃ�)
	// �Q�ƕԂ��͎��̂ŕԂ�(this�̓|�C���^�Ȃ̂�*�����Ď��̂�Ԃ�)
	// this�͂����̊֐����߲��
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

// �P�����Z�q
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
