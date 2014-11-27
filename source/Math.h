#pragma once

#include <cmath>

inline float Magnitude(float x, float y)
{
	return sqrt((x*x) + (y*y));
}

inline float Distance(float x1, float y1, float x2, float y2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	return Magnitude(x, y);
}

inline void Normalise(float& x, float& y)
{
	float mag = Magnitude(x, y);
	if(mag <= 0)
		x = 0, y = 0;
	else
		x = x / mag, y = y / mag;
}

inline float DirToRot(float xDir, float yDir)
{
	return (float)-(atan2f(yDir, xDir) * (180.f / 3.1415f) + 90);
}