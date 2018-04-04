#ifndef SAT_H
#define SAT_H

#include "Point.h"
#include "Pair.h"
#include "Vector.h"
#include "AABB.h"
#include "Circle.h"
#include <vector>
#include "../Utility/Utility.h"
#include "../Utility/Rotation.h"
#include "../Debug/Console.h"

struct CollisionResults
{
	CollisionResults(bool collided = false, PairFloat overlap = PairFloat(0.f, 0.f));

	bool _Collided;		//	Did a collision occur?
	Vec _Overlap;	//	What is the overlap on each axis?
};	

Vec Normal(Vec input);						//	Returns the left-hand normal (-input._Y, input._X)
float DotProduct(Vec v1, Vec v2);			//	Returns the dot product of two vectors (v1._X * v2._X) + (v1._Y * v2._Y)
std::vector<Vec> GenAABBNormals();			//	i.e. returns the x- and y-axis (1,0) and (0,1) as vectors
std::vector<Point> GenVertices(AABB box);	//	Returns the vertices (corners) for an AABB
PairFloat Project(std::vector<Point> vertices, Vec axis);	//	Returns the min & max for the projection of a shape onto an axis
PairFloat Project(Circle circ, Vec axis);
bool Overlaps(PairFloat p1, PairFloat p2);	//	Returns if the max projection of 1 shape is greater than the min of the other (or vice versa)
float CalcOverlap(PairFloat p1, PairFloat p2);	//	Calculates the magnitude of the overlap

CollisionResults SimpleAABBtoCircle(AABB box, Circle circ);
CollisionResults SATCheckAABBtoAABB(AABB box1, AABB box2);
CollisionResults SATCheckAABBtoCircle(AABB box, Circle circ);

//	Change Player Mask to AABB temporarily.
//	Then test it out - will never use it in practice (normal way is faster) but good to make sure we have the theory down
//	Then get Circle<->Circle working - again, never us it in practice
//	Then get AABB<->Circle working
//	Then expand to generic polygon v polygon, for future use
//	Then rejig Collision.h/.cpp to make us of SAT for AABB<->Circle checks

#endif