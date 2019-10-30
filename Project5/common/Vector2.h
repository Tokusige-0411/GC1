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
	Vector2Template operator == (const Vector2Template& vec)const;
	Vector2Template operator != (const Vector2Template& vec)const;
	Vector2Template operator > (const Vector2Template& vec)const;
	Vector2Template operator >= (const Vector2Template& vec)const;

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

using vector2Int = Vector2Template<int>;
using vector2Dbl = Vector2Template<double>;

#include "./detirlth/Vector2.h"