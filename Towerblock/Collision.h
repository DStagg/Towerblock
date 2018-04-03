#ifndef COLLISION_H
#define COLLISION_H

#include "Framework\Data\Pair.h"
#include "Framework\Data\AABB.h"
#include "Circle.h"
#include "Line.h"
#include "Vector.h"
#include "Rotation.h"

class AABBMask;
class CircleMask;

struct CollisionResults
{
	CollisionResults(bool collided = false, PairFloat overlap = PairFloat(0.f, 0.f));

	bool _Collided;		//	Did a collision occur?
	PairFloat _Overlap;	//	What is the overlap on each axis?
};	//	TODO: revamp CollisionResults. May need to know minor axis overlap too (e.g. diagonal landing on floor, move up by y over)

class CollisionMask
{
public:

	virtual CollisionResults Collide(CollisionMask& mask) = 0;
	virtual CollisionResults CollideWith(AABBMask& mask) = 0;
	virtual CollisionResults CollideWith(CircleMask& mask) = 0;
};

class AABBMask : public CollisionMask
{
public:

	CollisionResults Collide(CollisionMask& mask);
	CollisionResults CollideWith(AABBMask& mask);
	CollisionResults CollideWith(CircleMask& mask);
	
	AABB _Mask;
};

class CircleMask : public CollisionMask
{
public:

	CollisionResults Collide(CollisionMask& mask);
	CollisionResults CollideWith(AABBMask& mask);
	CollisionResults CollideWith(CircleMask& mask);

	Circle _Mask;
};

//	TODO: have the various collision functions actually return CollisionResults
bool PointWithinAABB(PairFloat point, AABB box);
bool PointWithinCircle(PairFloat point, Circle circ);
bool PointWithinLine(PairFloat point, Line line);

CollisionResults CollideAABBtoAABB(AABB box1, AABB box2);
CollisionResults CollideAABBtoCircle(AABB box, Circle circ);
CollisionResults CollideAABBtoLine(AABB box, Line line);

CollisionResults CollideCircletoAABB(Circle circ, AABB box);
CollisionResults CollideCircletoCircle(Circle circ1, Circle circ2);
CollisionResults CollideCircletoLine(Circle circ, Line line);

CollisionResults CollideLinetoAABB(Line line, AABB box);
CollisionResults CollideLinetoCircle(Line line, Circle circ);
CollisionResults CollideLinetoLine(Line line1, Line line2);

#endif