#include "AABB.h"

AABB::AABB()
{
	_X = 0;
	_Y = 0;
	_Width = 1;
	_Height = 1;
}

AABB::AABB(int x, int y, int w, int h)
{
	_X = x;
	_Y = y;
	_Width = w;
	_Height = h;
};

AABB::~AABB()
{

};

int AABB::Top()
{
	return _Y;
};
int AABB::Bottom()
{
	return _Y + _Height - 1;
};
int AABB::Left()
{
	return _X;
};
int AABB::Right()
{
	return _X + _Width - 1;
};

bool AABB::Contains(int x, int y)
{
	if ((x < _X) || (x > Right()))
		return false;
	if ((y < _Y) || (y > Bottom()))
		return false;
	return true;
};

bool AABB::Intersects(AABB box)
{
	if (box.Right() < _X)
		return false;
	if (box._X > Right())
		return false;
	if (box.Bottom() < _Y)
		return false;
	if (box._Y > Bottom())
		return false;
	return true;
};