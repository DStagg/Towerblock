#include "Collision.h"

//	Double Dispatch

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

//	Points

bool PointWithinAABB(PairFloat point, AABB box)
{
	if (point._X < box._X) return false;
	if (point._X > box.Right()) return false;
	if (point._Y < box._Y) return false;
	if (point._Y > box.Bottom()) return false;

	return true;
};

bool PointWithinCircle(PairFloat point, Circle circ)
{
	return CalcDistance(point._X, point._Y, circ._X, circ._Y) <= circ._Radius;
};

bool PointWithinLine(PairFloat point, Line line)
{
	float marginOfError = 0.000001f;
	return (CalcDistance(line._X1, line._Y1, point._X, point._Y) + CalcDistance(line._X2, line._Y2, point._X, point._Y)) - CalcDistance(line._X1, line._Y1, line._X2, line._Y2) < marginOfError;
};

//	AABB

CollisionResults CollideAABBtoAABB(AABB box1, AABB box2)
{
	if (box1.Right() < box2._X) return false;
	if (box1._X > box2.Right()) return false;
	if (box1.Bottom() < box2._Y) return false;
	if (box1._Y > box2.Bottom()) return false;
	return true;
};

CollisionResults CollideAABBtoCircle(AABB box, Circle circ)
{
	//	Based off of: https://gamedev.stackexchange.com/questions/96337/collision-between-aabb-and-circle
	
	//	Can do preliminary checks (is center of circ more than circ._R left of box._X, right of box._Right, etc.?
	//	6 collisions to test (check if center of circle is within each):
	PairFloat point(circ._X, circ._Y);
	//	1: is the center of the circle within a rectangle of width box._W + circ._R, laid accross the AABB?
	AABB widebox(box._X - circ._Radius, box._Y, box._Width + (circ._Radius * 2.f), box._Height);
	if (PointWithinAABB(point, widebox)) return true;
	//	2: is the center of the circle within a rectangle of height box._H + circ._R, laid accross the AABB?
	AABB tallbox(box._X, box._Y - circ._Radius, box._Width, box._Height + (circ._Radius * 2.f));
	if (PointWithinAABB(point, tallbox)) return true;
	//	3-6: is the center of the circle within a circle of radius circ._R on each of the four corners of the AABB?
	Circle c1(box._X, box._Y, circ._Radius);
	if (PointWithinCircle(point, c1)) return true;
	Circle c2(box.Right(), box._Y, circ._Radius);
	if (PointWithinCircle(point, c2)) return true;
	Circle c3(box._X, box.Bottom(), circ._Radius);
	if (PointWithinCircle(point, c3)) return true;
	Circle c4(box.Right(), box.Bottom(), circ._Radius);
	if (PointWithinCircle(point, c4)) return true;
	
	//	If all 6 return false, then there is no collision
	return false;
};

CollisionResults CollideAABBtoLine(AABB box, Line line)
{
	return false;	//	TODO: fill in AABB<->line collision
}

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
	float dist = (circ1._Radius + circ2._Radius) - CalcDistance(circ1._X, circ1._Y, circ2._X, circ2._Y);
	if (dist > 0.f)
	{
		PairFloat uvec = UnitVec(PairFloat(circ2._X - circ1._X, circ2._Y - circ1._Y));
		return CollisionResults(true, PairFloat(uvec._X * dist , uvec._Y * dist));
	}
	return CollisionResults();
};

CollisionResults CollideCircletoLine(Circle circ, Line line)
{
	return CollisionResults();	//	TODO: fill in circle<->line collision
};

//	Line

CollisionResults CollideLinetoAABB(Line line, AABB box)
{
	CollisionResults temp = CollideAABBtoLine(box, line);
	temp._Overlap._X = -temp._Overlap._X;
	temp._Overlap._Y = -temp._Overlap._Y;
	return temp;
};

CollisionResults CollideLinetoCircle(Line line, Circle circ)
{
	CollisionResults temp = CollideCircletoLine(circ, line);
	temp._Overlap._X = -temp._Overlap._X;
	temp._Overlap._Y = -temp._Overlap._Y;
	return temp;
};

CollisionResults CollideLinetoLine(Line line1, Line line2)
{
	return CollisionResults();	//	TODO: fill in line<->line collision
};
