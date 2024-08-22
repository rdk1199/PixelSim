#pragma once

#include <iostream>
#include <vector>


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

struct pixel
{
	int x;
	int y;
};

inline pixel operator+(const pixel& a, const pixel& b)
{
	return { a.x + b.x, a.y + b.y };
}

inline pixel operator-(const pixel& a, const pixel& b)
{
	return { a.x - b.x, a.y - b.y };
}

inline pixel operator*(int c, const pixel& a)
{
	return { c * a.x, c * a.y };
}

inline pixel& operator +=(pixel& a, const pixel& b)
{
	a = a + b;
	return a;
}

inline pixel operator/(const pixel& p, int c)
{
	return { p.x / c, p.y / c };
}

inline bool operator==(const pixel& a, const pixel& b)
{
	return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const pixel& a, const pixel& b)
{
	return !(a == b);
}

std::vector<pixel> compute_line(pixel start_px, pixel end_px); //returns all points on a (approximate) straight line from start to end, in order, always including start and end; line is guaranteed to fall in box defined by two pixels (i.e. no invalid pixels generated)