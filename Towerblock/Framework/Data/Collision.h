#ifndef COLLISION_H
#define COLLISION_H

#include "Shapes.h"

class AABBMask;
class CircleMask;

struct CollisionResults
{
	CollisionResults();
	CollisionResults(bool collided, Vec overlap);

	bool _Collided;		//	Did a collision occur?
	Vec _Overlap;		//	What is the overlap on each axis?
};

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

#endif