#ifndef POINT_H
#define POINT_H

#include "Framework\Data\Pair.h"

class Point
{
public:

	Point(int x, int y);
	Point(float x, float y);
	Point();

	int GetX();
	int GetY();
	void SetX(int x);
	void SetX(float x);
	void SetY(int y);
	void SetY(float y);
	void Set(int x, int y);
	void Set(float x, float y);

	Point operator+(const Point& p);
	Point operator-(const Point& p);
	Point operator*(const int& i);
	Point operator*(const float& f);
	Point operator*(const Point& p);
	Point operator/(const int& i);
	Point operator/(const float& f);
	Point operator/(const Point& p);
	void operator+=(const Point& p);
	void operator-=(const Point& p);
	void operator*=(const int& i);
	void operator*=(const float& f);
	void operator*=(const Point& p);
	void operator/=(const int& i);
	void operator/=(const float& f);
	void operator/=(const Point& p);
	
	bool operator==(const Point& p);
	
protected:

	PairFloat _Coords;
};

#endif