#ifndef PAIR_H
#define PAIR_H

template <class T>
struct Pair
{
	Pair()
	{

	};
	Pair(T x, T y)
	{
		Set(x, y);
	};

	void Set(T x, T y)
	{
		_X = x;
		_Y = y;
	};

	T _X;
	T _Y;
};

typedef Pair<float> PairFloat;
typedef Pair<int> PairInt;

PairFloat UnitVec(PairFloat input)
{
	float factor = sqrtf((input._X * input._X) + (input._Y * input._Y));
	return PairFloat(input._X / factor, input._Y / factor);
};

#endif