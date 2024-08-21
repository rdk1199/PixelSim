#pragma once

struct vec2
{
	float x;
	float y;
};

inline vec2 operator+(const vec2& a, const vec2& b)
{
	return { a.x + b.x, a.y + b.y};
}

inline vec2 operator*(float c, const vec2& v)
{
	return { c * v.x, c * v.y };
}