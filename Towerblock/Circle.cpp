#include "Circle.h"

Circle::Circle(int x, int y, int r)
{
	_X = x;
	_Y = y;
	_Radius = r;
};

bool Circle::Contains(int x, int y)
{
	int dX = x - _X;
	int dY = y - _Y;
	return (int)sqrtf(((float)dX * (float)dX) + ((float)dY * (float)dY)) <= _Radius;
}

bool Circle::Intersects(Circle c)
{
	int dX = c._X - _X;
	int dY = c._Y - _Y;
	return (int)sqrtf(((float)dX * (float)dX) + ((float)dY * (float)dY)) <= _Radius + c._Radius;
};