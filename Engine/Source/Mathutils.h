#pragma once
#include "Vector2.h"
#include <cmath>

namespace Math 
{
	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 6.28318530717f;
	constexpr float HalfPi = 1.57079632679f;

	constexpr float RadToDeg(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegToRad(float degrees) { return degrees * (Pi / 180.0f); }

	inline float Sin(float radians) { return std::sinf(radians); }

	inline float Cos(float radians) { return std::cosf(radians); }

	inline float Sqrt(float value) { return std::sqrtf(value); }

	inline float Atan2(float y, float x) { return std::atan2f(y, x); }

	/// <summary>
	/// Returns the maximum value of a and b
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a">value</param>
	/// <param name="b">value</param>
	/// <returns>The maximum value between a and b</returns>
	template<typename T>
	inline T Max(T a, T b) { return (a > b) ? a : b; }
	
	template<typename T>
	inline T Min(T a, T b) { return (a < b) ? a : b; }

	template<typename T>
	inline T Abs(T value) { return (value < 0) ? -value : value; }

	inline float Powf(float value, float power) { return std::pow(value, power); }

	template<typename T>
	inline T Clamp(T v, T min, T max) { return (v < min) ? min : (v > max) ? max : v; }

	inline int Wrap(int value, int max) { return value % max + ((value < 0) ? max : 0); }
	inline float Wrap(float value, float max) { return std::fmodf(value, max) + ((value < 0) ? max : 0); }	
}