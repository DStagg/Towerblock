#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sstream>
#include <fstream>

std::string IntToString(int i);

std::string FloatToString(float f);

int StringToInt(std::string s);

float StringToFloat(std::string s);

int Random(int min = 0, int max = RAND_MAX, bool inczero = true);

int RandomSign();

float Strip(float in, float factor = 100.f);

float FRound(float f);

template <class T>
bool IsOdd(T a)
{
	if ((((int)a) % 2) == 0)
		return false;
	return true;
};

template <class T>
bool IsEven(T a)
{
	return !IsOdd(a);
};

template <class T>
T Min(T a, T b)
{
	if (a <= b)
		return a;
	else
		return b;
};

template <class T>
T Max(T a, T b)
{
	if (a >= b)
		return a;
	else
		return b;
};

template <class T>
int Sign(T a)
{
	if (a < 0)
		return -1;
	if (a > 0)
		return 1;

	return 0;
};

template <class T>
T Abs(T a)
{
	if (a < 0)
		return -a;
	return a;
};

#endif