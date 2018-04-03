#ifndef CIRCLE_H
#define CIRCLE_H

#include <math.h>

class Circle
{
public:

	Circle(int x = 0, int y = 0, int r = 0);

	bool Contains(int x, int y);
	bool Intersects(Circle c);
	
	int _X, _Y, _Radius;
};

#endif