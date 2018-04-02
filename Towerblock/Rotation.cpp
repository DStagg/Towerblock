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
	return (float)atan2(endy - starty, endx - startx);
};

float CalcAngle(float dx, float dy)
{
	return CalcAngle(0.f, 0.f, dx, dy);
};

float CalcHeading(float startx, float starty, float endx, float endy)
{
	float result = CalcAngle(startx, starty, endx, endy) + (Pi / 2.f);
	if (result < 0.f) result += (Pi * 2.f);
	return result;
};

float CalcHeading(float dx, float dy)
{
	return CalcHeading(0.f, 0.f, dx, dy);
};

float CalcSFMLAngle(float startx, float starty, float endx, float endy)
{
	return CalcHeading(startx, starty, endx, endy) - 90.f;
};

float CalcXComp(float heading)
{
	return sinf(DegreeToRad(heading));
};

float CalcYComp(float heading)
{
	return cosf(DegreeToRad(heading));
};

float CalcDistance(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x2;
	float dy = y2 - y1;
	return sqrtf((dx * dx) + (dy * dy));
};