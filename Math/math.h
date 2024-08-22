#pragma once

#include <iostream>



struct vec2
{
	float x;
	float y;
};

inline vec2 operator+(const vec2& a, const vec2& b)
{
	return { a.x + b.x, a.y + b.y};
}

inline vec2& operator +=(vec2& a, const vec2& b)
{
	a = a + b;
	return a;
}

inline vec2 operator*(float c, const vec2& v)
{
	return { c * v.x, c * v.y };
}

inline vec2 operator/(const vec2& v, float c)
{
	return { v.x / c, v.y / c };
}

inline std::ostream& operator<<(std::ostream& stream, const vec2& v)
{
	stream << v.x << ", " << v.y;
	return stream;
}