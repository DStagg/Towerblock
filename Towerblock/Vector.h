#ifndef VECTOR_H
#define VECTOR_H

#include "Framework\Data\Pair.h"
#include <math.h>

class Vec : public PairFloat
{
	Vec(float x = 0.f, float y = 0.f);
	Vec(PairFloat p);

	Vec UnitVec();
	float Length();

	Vec operator+(const Vec& v);
	Vec operator-(const Vec& v);
	Vec operator*(const int& i);
	Vec operator*(const float& f);
	Vec operator*(const Vec& v);
	Vec operator/(const int& i);
	Vec operator/(const float& f);
	Vec operator/(const Vec& v);

};

#endif