#ifndef ROTATION_H
#define ROTATION_H

#include <math.h>

#define Pi 3.14159265358979323846264f

float DegreeToRad(float d);

float RadToDegree(float r);

float CalcAngle(float startx, float starty, float endx, float endy);
//	Left is -180, Up is -90, Right is 0, Down is 90

float CalcHeading(float startx, float starty, float endx, float endy);
//	Up is 0, Right is 90, Down is 180, Left is 270

//	TODO: add functions to convert between the angle system I use and the angle system SFML uses.

#endif