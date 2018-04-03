#include "Point.h"

//	Constructors/Deconstructor

Point::Point(int x, int y)
{
	Set(x, y);
};
Point::Point(float x, float y)
{
	Set(x, y);
};
Point::Point()
{
	Set(0, 0);
};

//	Get/Set

int Point::GetX()
{
	return (int)_Coords._X;
};
int Point::GetY()
{
	return (int)_Coords._Y);
};
void Point::SetX(int x)
{
	_Coords._X = (float)x;
};
void Point::SetX(float x)
{
	_Coords._X = x;
};
void Point::SetY(int y)
{
	_Coords._Y = (float)y;
};
void Point::SetY(float y)
{
	_Coords._Y = y;
};
void Point::Set(int x, int y)
{
	SetX(x);
	SetY(y);
};
void Point::Set(float x, float y)
{
	SetX(x);
	SetY(y);
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
void Point::operator-=(const Point& p)
{
	_Coords.Set(_Coords._X - p._Coords._X, _Coords._Y - p._Coords._Y);
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

bool Point::operator==(const Point& p)
{
	return (GetX() == p.GetX()) && (GetY() == p.GetY());
};