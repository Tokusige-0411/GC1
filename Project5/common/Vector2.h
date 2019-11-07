#pragma once

template<class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x;
	T y;

	// ë„ì¸ââéZéq
	Vector2Template& operator = (const Vector2Template& vec);

	// ìYÇ¶éöââéZéq
	Vector2Template& operator [] (T i);

	// î‰ärââéZéq
	bool operator == (const Vector2Template& vec)const;
	bool operator != (const Vector2Template& vec)const;
	bool operator > (const Vector2Template& vec)const;
	bool operator >= (const Vector2Template& vec)const;

	// íPçÄââéZéq
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (Vector2Template k);
	Vector2Template& operator /= (Vector2Template k);
	Vector2Template operator + ()const;
	Vector2Template operator - ()const;
};

// ===========================Õﬁ∏ƒŸÇÃââéZ===================================
// Vector2 + int
template<class T>
Vector2Template<T> operator+(const Vector2Template<T>& u, const T k);

// Vector2 - int
template<class T>
Vector2Template<T> operator-(const Vector2Template<T>& u, const T k);

// Vector2 + Vector2
template<class T>
Vector2Template<T> operator+(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 - Vector2
template<class T>
Vector2Template<T> operator-(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 * Vector2
template<class T>
Vector2Template<T> operator*(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 / Vector2
template<class T>
Vector2Template<T> operator/(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 % Vector2
template<class T>
Vector2Template<T> operator%(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 % int
template<class T>
Vector2Template<T> operator%(const Vector2Template<T>& u, const T k);

// Vector2 * int
template<class T>
Vector2Template<T> operator*(const Vector2Template<T>& u, const T k);

// int * Vector2
template<class T>
Vector2Template<T> operator*(const T k, const Vector2Template<T>& u);

// Vector2 / int
template<class T>
Vector2Template<T> operator/(const Vector2Template<T>& u, const T k);

// absÇ…ïœä∑
template<class T>
Vector2Template<T> abs(const Vector2Template<T>& u);

using vector2Int = Vector2Template<int>;
using vector2Dbl = Vector2Template<double>;

#include "./detirlth/Vector2.h"