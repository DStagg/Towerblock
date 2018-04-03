#ifndef POINT_H
#define POINT_H

#include "Pair.h"

class Vec;

class Point
{
public:

	Point(int x, int y);
	Point(float x, float y);
	Point(Vec v);
	Point();

	int getX();
	int getY();
	PairInt get();
	void setX(int x);
	void setX(float x);
	void setY(int y);
	void setY(float y);
	void set(int x, int y);
	void set(float x, float y);

	Point operator+(const Point& p);
	Point operator-(const Point& p);
	Point operator*(const int& i);
	Point operator*(const float& f);
	Point operator*(const Point& p);
	Point operator/(const int& i);
	Point operator/(const float& f);
	Point operator/(const Point& p);
	void operator+=(const Point& p);
	void operator+=(const Vec& v);
	void operator-=(const Point& p);
	void operator-=(const Vec& v);
	void operator*=(const int& i);
	void operator*=(const float& f);
	void operator*=(const Point& p);
	void operator/=(const int& i);
	void operator/=(const float& f);
	void operator/=(const Point& p);
	
	bool operator==(Point& p);
	
protected:

	PairFloat _Coords;
};

#endif