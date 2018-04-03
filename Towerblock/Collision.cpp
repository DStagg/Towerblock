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

//	Points

bool PointWithinAABB(Point point, AABB box)
{
	return box.Contains(point.getX(), point.getY());
};

bool PointWithinCircle(Point point, Circle circ)
{
	return circ.Contains(point.getX(), point.getY());
};

bool PointWithinLine(Point point, Line line)
{
	float marginOfError = 0.000001f;
	return (CalcDistance(line._X1, line._Y1, (float)point.getX(), (float)point.getY()) + CalcDistance(line._X2, line._Y2, (float)point.getX(), (float)point.getY())) - CalcDistance(line._X1, line._Y1, line._X2, line._Y2) < marginOfError;
};

//	AABB

CollisionResults CollideAABBtoAABB(AABB box1, AABB box2)
{
	//	Based off of: https://hamaluik.com/posts/simple-aabb-collision-using-minkowski-difference/
	//	TLDR: sum the two boxes together, if the result covers (0,0) then they intersect
	//			the minimum escape vector is then whichever cardinal direction is closest to 0

	AABB minkowski(box1.Left() - box2.Right(), box1.Top() - box2.Bottom(), box1._Width + box2._Width, box1._Height + box2._Height);
	if (!minkowski.Contains(0, 0))
		return false;

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

CollisionResults CollideAABBtoCircle(AABB box, Circle circ)
{
	//	Based off of: https://gamedev.stackexchange.com/questions/96337/collision-between-aabb-and-circle
	
	//	Can do preliminary checks (is center of circ more than circ._R left of box._X, right of box._Right, etc.?
	//	6 collisions to test (check if center of circle is within each):
	Point point(circ._X, circ._Y);
	//	1: is the center of the circle within a rectangle of width box._W + circ._R, laid accross the AABB?
	AABB widebox(box._X - circ._Radius, box._Y, box._Width + (circ._Radius * 2.f), box._Height);
	if (PointWithinAABB(point, widebox))
		return true;
	//	2: is the center of the circle within a rectangle of height box._H + circ._R, laid accross the AABB?
	AABB tallbox(box._X, box._Y - circ._Radius, box._Width, box._Height + (circ._Radius * 2.f));
	if (PointWithinAABB(point, tallbox))
		return true;
	//	3-6: is the center of the circle within a circle of radius circ._R on each of the four corners of the AABB?
	Circle c1(box._X, box._Y, circ._Radius);		//	Top-Left
	if (PointWithinCircle(point, c1))
		return true;
	Circle c2(box.Right(), box._Y, circ._Radius);	//	Top-Right
	if (PointWithinCircle(point, c2)) return true;
	Circle c3(box._X, box.Bottom(), circ._Radius);	//	Bottom-Left
	if (PointWithinCircle(point, c3)) return true;
	Circle c4(box.Right(), box.Bottom(), circ._Radius);	//	Bottom-Right
	if (PointWithinCircle(point, c4)) return true;
	
	//	If all 6 return false, then there is no collision
	return CollisionResults(false);
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
		Vec uvec = (Vec(circ2._X, circ2._Y) - Vec(circ1._X , circ1._Y)).UnitVec();
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
