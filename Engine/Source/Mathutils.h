#pragma once
#include <cmath>

namespace Math 
{
	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 6.28318530717f;
	constexpr float HalfPi = 1.57079632679f;

	constexpr float RadToDeg(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegToRad(float degrees) { return degrees * (Pi / 180.0f); }

	float Sin(float radians)
	{
		return std::sinf(radians);
	}

	float Cos(float radians)
	{
		return std::cosf(radians);
	}

	/// <summary>
	/// Returns the maximum value of a and b
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a">value</param>
	/// <param name="b">value</param>
	/// <returns>The maximum value between a and b</returns>
	template<typename T>
	T Max(T a, T b) { return (a > b) ? a : b; }
	
	template<typename T>
	T Min(T a, T b) { return (a < b) ? a : b; }

	template<typename T>
	T Abs(T value) { return (value < 0) ? -value : value; }
}