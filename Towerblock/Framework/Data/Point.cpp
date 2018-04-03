#include "Point.h"
#include "Vector.h"

//	Constructors/Deconstructor

Point::Point(int x, int y)
{
	set(x, y);
};
Point::Point(float x, float y)
{
	set(x, y);
};
Point::Point(Vec v)
{
	set(v._X, v._Y);
};
Point::Point()
{
	set(0, 0);
};

//	Get/Set

int Point::getX()
{
	return (int)_Coords._X;
};
int Point::getY()
{
	return (int)_Coords._Y;
};
PairInt Point::get()
{
	return PairInt((int)_Coords._X, (int)_Coords._Y);
};
void Point::setX(int x)
{
	_Coords._X = (float)x;
};
void Point::setX(float x)
{
	_Coords._X = x;
};
void Point::setY(int y)
{
	_Coords._Y = (float)y;
};
void Point::setY(float y)
{
	_Coords._Y = y;
};
void Point::set(int x, int y)
{
	setX(x);
	setY(y);
};
void Point::set(float x, float y)
{
	setX(x);
	setY(y);
};

//	Operators

Point Point::operator+(const Point& p)
{
	return Point(_Coords._X + p._Coords._X, _Coords._Y + p._Coords._Y);
};
Point Point::operator-(const Point& p)
{
	return Point(_Coords._X - p._Coords._X, _Coords._Y - p._Coords._Y);
};
Point Point::operator*(const int& i)
{
	return Point(_Coords._X * (float)i, _Coords._Y * (float)i);
};
Point Point::operator*(const float& f)
{
	return Point(_Coords._X * f, _Coords._Y * f);
};
Point Point::operator*(const Point& p)
{
	return Point(_Coords._X * p._Coords._X, _Coords._Y * p._Coords._Y);
};
Point Point::operator/(const int& i)
{
	return Point(_Coords._X / (float)i, _Coords._Y / (float)i);
};
Point Point::operator/(const float& f)
{
	return Point(_Coords._X / f, _Coords._Y / f);
};
Point Point::operator/(const Point& p)
{
	return Point(_Coords._X / p._Coords._X, _Coords._Y / p._Coords._Y);
};
void Point::operator+=(const Point& p)
{
	_Coords.Set(_Coords._X + p._Coords._X, _Coords._Y + p._Coords._Y);
};
void Point::operator+=(const Vec& v)
{
	_Coords.Set(_Coords._X + v._X, _Coords._Y + v._Y);
};
void Point::operator-=(const Point& p)
{
	_Coords.Set(_Coords._X - p._Coords._X, _Coords._Y - p._Coords._Y);
};
void Point::operator-=(const Vec& v)
{
	_Coords.Set(_Coords._X - v._X, _Coords._Y - v._Y);
};
void Point::operator*=(const int& i)
{
	_Coords.Set(_Coords._X * (float)i, _Coords._Y * (float)i);
};
void Point::operator*=(const float& f)
{
	_Coords.Set(_Coords._X * f, _Coords._Y * f);
};
void Point::operator*=(const Point& p)
{
	_Coords.Set(_Coords._X * p._Coords._X, _Coords._Y * p._Coords._Y);
};
void Point::operator/=(const int& i)
{
	_Coords.Set(_Coords._X / (float)i, _Coords._Y / (float)i);
};
void Point::operator/=(const float& f)
{
	_Coords.Set(_Coords._X / f, _Coords._Y / f);
};
void Point::operator/=(const Point& p)
{
	_Coords.Set(_Coords._X / p._Coords._X, _Coords._Y / p._Coords._Y);
};

bool Point::operator==(Point& p)
{
	return (getX() == p.getX()) && (getY() == p.getY());
};