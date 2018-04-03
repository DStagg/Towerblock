#include "Collision.h"

//	Double Dispatch

AABBMask::AABBMask(AABB box)
{
	_Mask = box;
}

CollisionResults AABBMask::Collide(CollisionMask& mask)
{
	return mask.CollideWith(*this);
};
CollisionResults AABBMask::CollideWith(AABBMask& mask)
{
	return CollideAABBtoAABB(_Mask, mask._Mask);
};
CollisionResults AABBMask::CollideWith(CircleMask& mask)
{
	return CollideAABBtoCircle(_Mask, mask._Mask);
};

CircleMask::CircleMask(Circle circ)
{
	_Mask = circ;
};

CollisionResults CircleMask::Collide(CollisionMask& mask)
{
	return mask.CollideWith(*this);
};
CollisionResults CircleMask::CollideWith(AABBMask& mask)
{
	return CollideCircletoAABB(_Mask, mask._Mask);
};
CollisionResults CircleMask::CollideWith(CircleMask& mask)
{
	return CollideCircletoCircle(_Mask, mask._Mask);
};

//	Collision Results

CollisionResults::CollisionResults(bool collided, PairFloat overlap)
{
	_Collided = collided;
	_Overlap = overlap;
};

//	AABB

CollisionResults CollideAABBtoAABB(AABB box1, AABB box2)
{
	//	Based off of: https://hamaluik.com/posts/simple-aabb-collision-using-minkowski-difference/
	//	TLDR: sum the two boxes together, if the result covers (0,0) then they intersect
	//			the minimum escape vector is then whichever cardinal direction is closest to 0

	AABB minkowski(box1.Left() - box2.Right(), box1.Top() - box2.Bottom(), box1._Width + box2._Width, box1._Height + box2._Height);
	if (!minkowski.Contains(0, 0))
		return CollisionResults(false);

	int minDist = Abs(minkowski.Left());	//	Left
	Vec minVec((float)minkowski.Left(), 0.f);

	if (Abs(minkowski.Right()) < minDist)	//	Right
	{
		minDist = Abs(minkowski.Right());
		minVec.Set((float)minkowski.Right(), 0.f);
	}
	if (Abs(minkowski.Bottom()) < minDist)	//	Bottom
	{
		minDist = Abs(minkowski.Bottom());
		minVec.Set(0.f, (float)minkowski.Bottom());
	}
	if (Abs(minkowski.Top()) < minDist)		//	Top
	{
		minDist = Abs(minkowski.Top());
		minVec.Set(0.f, (float)minkowski.Top());
	}

	return CollisionResults(true, minVec);
};
//	TODO: get min. sep. vec for AABB<->Circle collisions.
CollisionResults CollideAABBtoCircle(AABB box, Circle circ)
{
	//	Based off of: https://gamedev.stackexchange.com/questions/96337/collision-between-aabb-and-circle
	
	//	Can do preliminary checks (is center of circ more than circ._R left of box._X, right of box._Right, etc.?
	//	6 collisions to test (check if center of circle is within each):
	Point point(circ._X, circ._Y);
	//	1: is the center of the circle within a rectangle of width box._W + circ._R, laid accross the AABB?
	AABB widebox(box._X - circ._Radius, box._Y, box._Width + (circ._Radius * 2), box._Height);
	if (widebox.Contains(point.getX(), point.getY()))
		return CollisionResults(true);
	//	2: is the center of the circle within a rectangle of height box._H + circ._R, laid accross the AABB?
	AABB tallbox(box._X, box._Y - circ._Radius, box._Width, box._Height + (circ._Radius * 2));
	if (tallbox.Contains(point.getX(), point.getY()))
		return CollisionResults(true);
	//	3-6: is the center of the circle within a circle of radius circ._R on each of the four corners of the AABB?
	Circle c1(box._X, box._Y, circ._Radius);		//	Top-Left
	if (c1.Contains(point.getX(), point.getY()))
		return CollisionResults(true);
	Circle c2(box.Right(), box._Y, circ._Radius);	//	Top-Right
	if (c2.Contains(point.getX(), point.getY()))
		return CollisionResults(true);
	Circle c3(box._X, box.Bottom(), circ._Radius);	//	Bottom-Left
	if (c3.Contains(point.getX(), point.getY()))
		return CollisionResults(true);
	Circle c4(box.Right(), box.Bottom(), circ._Radius);	//	Bottom-Right
	if (c4.Contains(point.getX(), point.getY()))
		return CollisionResults(true);
	
	//	If all 6 return false, then there is no collision
	return CollisionResults(false);
};

//	Circle

CollisionResults CollideCircletoAABB(Circle circ, AABB box)
{
	CollisionResults temp = CollideAABBtoCircle(box, circ);
	temp._Overlap._X = -temp._Overlap._X;
	temp._Overlap._Y = -temp._Overlap._Y;
	return temp;
};

CollisionResults CollideCircletoCircle(Circle circ1, Circle circ2)
{
	float dist = (float)(circ1._Radius + circ2._Radius) - CalcDistance((float)circ1._X, (float)circ1._Y, (float)circ2._X, (float)circ2._Y);
	if (dist > 0.f)
	{
		Vec uvec = (Vec((float)circ2._X, (float)circ2._Y) - Vec((float)circ1._X , (float)circ1._Y)).UnitVec();
		return CollisionResults(true, PairFloat(uvec._X * dist , uvec._Y * dist));
	}
	return CollisionResults();
};