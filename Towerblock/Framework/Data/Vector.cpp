#include "Vector.h"

Vec::Vec(float x, float y) : PairFloat(x, y)
{

};

Vec::Vec(PairFloat p) : Vec(p._X, p._Y)
{

};

Vec Vec::UnitVec()
{
	return Vec(_X, _Y) / Length();
};
float Vec::Length()
{
	return sqrtf((_X * _X) + (_Y * _Y));
};

Vec Vec::operator+(const Vec& v)
{
	return Vec(_X + v._X, _Y + v._Y);
};
Vec Vec::operator-(const Vec& v)
{
	return Vec(_X - v._X, -v._Y);
};
Vec Vec::operator*(const int& i)
{
	return Vec(_X * (float)i, _Y * (float)i);
};
Vec Vec::operator*(const float& f)
{
	return Vec(_X * f, _Y * f);
};
Vec Vec::operator*(const Vec& v)
{
	return Vec(_X * v._X, _Y * v._Y);
};
Vec Vec::operator/(const int& i)
{
	return Vec(_X / (float)i, _Y / (float)i);
};
Vec Vec::operator/(const float& f)
{
	return Vec(_X / f, _Y / f);
};
Vec Vec::operator/(const Vec& v)
{
	return Vec(_X / v._X, _Y / v._Y);
};
void Vec::operator+=(const Vec& v)
{
	_X += v._X;
	_Y += v._Y;
};
void Vec::operator-=(const Vec& v)
{
	_X -= v._X;
	_Y -= v._Y;
};
void Vec::operator*=(const int& i)
{
	_X *= (float)i;
	_Y *= (float)i;
};
void Vec::operator*=(const float& f)
{
	_X *= f;
	_Y *= f;
};
void Vec::operator*=(const Vec& v)
{
	_X *= v._X;
	_Y *= v._Y;
};
void Vec::operator/=(const int& i)
{
	_X /= (float)i;
	_Y /= (float)i;
};
void Vec::operator/=(const float& f)
{
	_X /= f;
	_Y /= f;
};
void Vec::operator/=(const Vec& v)
{
	_X /= v._X;
	_Y /= v._Y;
};