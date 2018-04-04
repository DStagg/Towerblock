#ifndef COLLISION_H
#define COLLISION_H

#include "Pair.h"
#include "AABB.h"
#include "Circle.h"
#include "Line.h"
#include "Vector.h"
#include "..\Utility\Rotation.h"
#include "Point.h"
#include "..\Utility\Utility.h"
#include "SAT.h"

class AABBMask;
class CircleMask;

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

	AABBMask(AABB box = AABB());

	CollisionResults Collide(CollisionMask& mask);
	CollisionResults CollideWith(AABBMask& mask);
	CollisionResults CollideWith(CircleMask& mask);
	
	AABB _Mask;
};

class CircleMask : public CollisionMask
{
public:

	CircleMask(Circle circ = Circle());

	CollisionResults Collide(CollisionMask& mask);
	CollisionResults CollideWith(AABBMask& mask);
	CollisionResults CollideWith(CircleMask& mask);

	Circle _Mask;
};

CollisionResults CollideAABBtoAABB(AABB box1, AABB box2);
CollisionResults CollideAABBtoCircle(AABB box, Circle circ);

CollisionResults CollideCircletoAABB(Circle circ, AABB box);
CollisionResults CollideCircletoCircle(Circle circ1, Circle circ2);

#endif