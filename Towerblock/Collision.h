#ifndef COLLISION_H
#define COLLISION_H

#include "Framework\Data\Pair.h"
#include "Framework\Data\AABB.h"
#include "Circle.h"
#include "Line.h"

#include "Rotation.h"

struct CollisionResults
{
	CollisionResults(bool collided = false, int axis = 0, float over = 0.f);

	enum Axis
	{
		X = 0,
		Y
	};

	bool _Collided;	//	Did a collision occur?
	int _MajorAxis;	//	Which axis (x or y) did the greatest degree of overlap occur on?
	float _Overlap;	//	What is the greatest degree of overlap?
};	//	TODO: revamp CollisionResults. May need to know minor axis overlap too (e.g. diagonal landing on floor, move up by y over)

bool PointWithinAABB(PairFloat point, AABB box);
bool PointWithinCircle(PairFloat point, Circle circ);
bool PointWithinLine(PairFloat point, Line line);
bool CollideAABBtoAABB(AABB box1, AABB box2);
bool CollideAABBtoCircle(AABB box, Circle circ);
bool CollideAABBtoLine(AABB box, Line line);
bool CollideCircletoAABB(Circle circ, AABB box);
bool CollideCircletoCircle(Circle circ1, Circle circ2);
bool CollideCircletoLine(Circle circ, Line line);
bool CollideLinetoAABB(Line line, AABB box);
bool CollideLinetoCircle(Line line, Circle circ);
bool CollideLinetoLine(Line line1, Line line2);

#endif
