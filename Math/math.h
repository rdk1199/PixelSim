#pragma once

#include <iostream>
#include <vector>
#include <cmath>

struct pixel
{
	int x;
	int y;
};

struct vec2
{
	float x;
	float y;

	float sq_mag() const { return x * x + y * y; }
	float mag() const { return sqrt(sq_mag()); }

	vec2 normalized() const { return { x / mag(), y / mag() }; } //return a normalized copy, preserving original
	void normalize() { x = x / mag(); y = y / mag(); } //normalize this vector, changing its values 

	vec2 rotated(float angle) const { angle = angle * (3.1415927 / 180.0f);  return { x * cos(angle) - y * sin(angle) , x * sin(angle) + y * cos(angle) }; } //rotates vector by angle DEGREES

	vec2 project_along(const vec2& dir);

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

inline float operator*(const vec2& a, const vec2& b) //dot product
{
	return a.x * b.x + a.y * b.y;
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