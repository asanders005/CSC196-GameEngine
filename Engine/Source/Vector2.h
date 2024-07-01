#pragma once
#include <cmath>

struct Vector2
{
	float x;
	float y;

	Vector2() = default;
	Vector2(float x, float y) { this->x = x; this->y = y; }
	Vector2(int x, int y) { this->x = x; this->y = y; }

	Vector2 operator + (Vector2 v) const { return Vector2{ x + v.x, y + v.y }; }
	Vector2 operator - (Vector2 v) const { return Vector2{ x - v.x, y - v.y }; }
	Vector2 operator * (Vector2 v) const { return Vector2{ x * v.x, y * v.y }; }
	Vector2 operator / (Vector2 v) const { return Vector2{ x / v.x, y / v.y }; }

	Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
	Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
	Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
	Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

	float LengthSqr(Vector2 v1, Vector2 v2) { return (v1.x * v2.x) + (v1.y * v2.y); }
	float Length(Vector2 v1, Vector2 v2) { return std::sqrt((v1.x * v2.x) + (v1.y * v2.y)); }
};