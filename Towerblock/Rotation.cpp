#include "Rotation.h"

float DegreeToRad(float d)
{
	float Temp = (d / 360.f) * 2.f * (float)Pi;
	return Temp;
};

float RadToDegree(float r)
{
	float TwoPi = 2.f * (float)Pi;
	float Temp = (r / TwoPi) * 360.f;
	return Temp;
};

float CalcAngle(float startx, float starty, float endx, float endy)
{
	return RadToDegree((float)atan2(endy - starty, endx - startx));
};

float CalcHeading(float startx, float starty, float endx, float endy)
{
	float Deg = CalcAngle(startx, starty, endx, endy);

	Deg += 90.f;

	if (Deg < 0.f)
		Deg += 360.f;
	if (Deg >= 359.999f)
		Deg = 0.f;

	return Deg;
};

float CalcSFMLAngle(float startx, float starty, float endx, float endy)
{
	return CalcHeading(startx, starty, endx, endy);
};