#include "Utility.h"

std::string IntToString(int i)
{

	std::stringstream out;
	out << i;
	return out.str();

};


std::string FloatToString(float f)
{

	std::stringstream out;
	out << f;
	return out.str();

};

int StringToInt(std::string s)
{
	int temp;
	std::stringstream(s) >> temp;

	return temp;
};

float StringToFloat(std::string s)
{
	float temp;
	std::stringstream(s) >> temp;

	return temp;
};

int Random(int min, int max, bool inczero)
{
	int value = rand() % (max - min + 1) + min;

	if ((inczero == false) && (value == 0))
		return Random(min, max, inczero);
	else
		return value;
};

int RandomSign()
{
	return Random(-1, 1, false);
};

float Strip(float in, float factor)
{
	return floor(in * factor) / factor;
};

float FRound(float f)
{
	float dump;
	float temp = modf(f, &dump);
	if (temp >= 0.5f)
		return ceil(f);
	else
		return floor(f);
};