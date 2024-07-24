#pragma once
#include "Mathutils.h"
#include <cmath>

struct Vector2
{
	float x;
	float y;

	Vector2() = default;
	Vector2(float x, float y) { this->x = x; this->y = y; }
	Vector2(int x, int y) { this->x = (float)x; this->y = (float)y; }

	float operator [] (unsigned int index) const { return (&x)[index]; }
	float& operator [] (unsigned int index) { return (&x)[index]; }

	Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
	Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
	Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
	Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

	Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
	Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
	Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
	Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

	Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
	Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

	Vector2& operator += (float s) { x += s; y += s; return *this; }
	Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
	Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
	Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

	float LengthSqr() const { return (x * x) + (y * y); }
	float Length() const { return Math::Sqrt((x * x) + (y * y)); }

	float Angle() const { return Math::Atan2(y, x); }
	Vector2 Rotate(float radians) const;

	Vector2 Normalized() const { return *this / Length(); }

	static Vector2 Wrap(const Vector2& v, const Vector2& max) { return Vector2{ Math::Wrap(v.x, max.x), Math::Wrap(v.y, max.y) }; }

	static Vector2 Clamp(Vector2 v, Vector2 min, Vector2 max) 
	{ 
		v.x = (v.x < min.x) ? min.x : (v.x > max.x) ? max.x : v.x;
		v.y = (v.y < min.y) ? min.y : (v.y > max.y) ? max.y : v.y;
		return v;
	}
};

inline Vector2 Vector2::Rotate(float radians) const
{
	float x_ = x * Math::Cos(radians) - y * Math::Sin(radians);
	float y_ = x * Math::Sin(radians) + y * Math::Cos(radians);

	return { x_, y_ };
}