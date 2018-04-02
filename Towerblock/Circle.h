#ifndef CIRCLE_H
#define CIRCLE_H

struct Circle
{
	Circle(float x = 0.f, float y = 0.f, float r = 0.f)
	{
		_X = x;
		_Y = y;
		_Radius = r;
	}
	float _X, _Y, _Radius;
};

#endif