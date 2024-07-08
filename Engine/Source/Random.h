#pragma once
#include "Vector2.h"
#include "Mathutils.h"
#include <random>

inline int random() { return rand(); }
inline int random(unsigned int max) { return rand() % max;}
inline int random(int min, int max) { return min + random(max - min); }

inline float randomf() { return rand() / (float)RAND_MAX; }
inline float randomf(float max) { return max * randomf(); }
inline float randomf(float min, float max) { return min + randomf(max - min); }

inline Vector2 randomOnUnitCircle() 
{
	float angle = randomf(0, 360);
	return Vector2{ Math::Cos(Math::DegToRad(angle)), Math::Sin(Math::DegToRad(angle)) };
}