#ifndef ROTATION_H
#define ROTATION_H
//	TODO: move to framework folders
#include <math.h>

#define Pi 3.14159265358979323846264f

float DegreeToRad(float d);

float RadToDegree(float r);
//	TODO: reconcile calculations in Rotation.h with switch to int-based coordinate system
float CalcAngle(float startx, float starty, float endx, float endy);
//	Returns the angle between two points relative to the x-axis in radians
//	Right is 0, Down is Pi/2, Left is Pi, Up is -Pi/2
//	Top half of semicircle is -Pi to 0, Bottom half is Pi to 0 (both left to right)

float CalcAngle(float dx, float dy);
//	Returns the angle between a vector and the x-axis in radians
//	Right is 0, Down is Pi/2, Left is Pi, Up is -Pi/2
//	Top half of semicircle is -Pi to 0, Bottom half is Pi to 0 (both left to right)

float CalcHeading(float startx, float starty, float endx, float endy);
//	Returns the heading of a vector between two points relative to the y-axis in radians
//	Right is 1.5 Pi, Down is Pi, Right is 0.f Pi, Up is 0

float CalcHeading(float dx, float dy);
//	Returns the heading of a vector relative to the y-axis in radians
//	Right is 1.5 Pi, Down is Pi, Right is 0.f Pi, Up is 0

float CalcSFMLAngle(float startx, float starty, float endx, float endy);
//	Up is 0, Right is 90, Down is 180, Left is 270
//	Just returns CalcHeading()

float CalcXComp(float heading);
//	Calculates the x-axis component of a given heading (i.e. sin(heading))

float CalcYComp(float heading);
//	Calculates the y-axis component of a given heading (i.e. cos(heading))
//	Offset by Pi/2 (90deg) to work.

float CalcDistance(float x1, float y1, float x2, float y2);
//	Calculates the distance between two points. Always positive.
float CalcDistance(int x1, int y1, int x2, int y2);

#endif