#include "SAT.h"

//	Collision Results

CollisionResults::CollisionResults(bool collided, PairFloat overlap)
{
	_Collided = collided;
	_Overlap = overlap;
};

/////////////////////

Vec Normal(Vec input)			
{
	return Vec(-input._Y, input._X);
};

float DotProduct(Vec v1, Vec v2)
{
	return (v1._X * v2._X) + (v1._Y * v2._Y);
};

std::vector<Vec> GenAABBNormals()
{
	std::vector<Vec> results;
	results.push_back(Vec(1, 0));
	results.push_back(Vec(0, 1));
	return results;
};

std::vector<Point> GenVertices(AABB box)
{
	std::vector<Point> results;
	results.push_back(Point(box.Left(), box.Top()));
	results.push_back(Point(box.Right(), box.Top()));
	results.push_back(Point(box.Right(), box.Bottom()));
	results.push_back(Point(box.Left(), box.Bottom()));
	return results;
};

PairFloat Project(std::vector<Point> vertices, Vec axis)
{
	if ((int)vertices.size() == 0)
		return PairFloat(0.f,0.f);

	//	_X is min, _Y is max, start both off as the projection of the first vertice
	PairFloat results(DotProduct(Vec((float)vertices[0].getX(), (float)vertices[0].getY()), axis), DotProduct(Vec((float)vertices[0].getX(), (float)vertices[0].getY()), axis));

	for (int i = 0; i < (int)vertices.size(); i++)
	{
		float p = DotProduct(Vec((float)vertices[i].getX(), (float)vertices[i].getY()), axis);
		if (p < results._X)
			results._X = p;
		else if (p > results._Y)
			results._Y = p;
	}
	
	return results;
};

PairFloat Project(Circle circ, Vec axis)
{
	float min = DotProduct(Vec((float)circ._X, (float)circ._Y) - (axis.UnitVec() * circ._Radius), axis);
	float max = DotProduct(Vec((float)circ._X, (float)circ._Y) + (axis.UnitVec() * circ._Radius), axis);
	
	return PairFloat(min, max);
};

bool Overlaps(PairFloat p1, PairFloat p2)
{
	//	_X is min, _Y is max
	if (p1._Y < p2._X) return false;
	if (p1._X > p2._Y) return false;
	if (p2._Y < p1._X) return false;
	if (p2._X > p1._Y) return false;
	return true;
};

float CalcOverlap(PairFloat p1, PairFloat p2)
{
	float d1 = p1._Y - p2._X;
	float d2 = p2._Y - p1._X;

	return Min(Abs(d1), Abs(d2));
};

CollisionResults SATCheckAABBtoAABB(AABB box1, AABB box2)
{
	//	Based on: http://www.dyn4j.org/2010/01/sat/#sat-mtv

	std::vector<Point> v1 = GenVertices(box1);
	std::vector<Point> v2 = GenVertices(box2);

	std::vector<Vec> axes = GenAABBNormals();

	Vec minAxis = axes[0];
	float minOver = 1000000.f;

	for (int i = 0; i < (int)axes.size(); i++)
	{
		PairFloat p1 = Project(v1, axes[i]);
		PairFloat p2 = Project(v2, axes[i]);

		if (!Overlaps(p1, p2))
			return CollisionResults(false);

		if (Abs(CalcOverlap(p1, p2)) < minOver)
		{
			minOver = CalcOverlap(p1, p2);
			minAxis = axes[i];
		}
	}

	return CollisionResults(true, minAxis.UnitVec() * minOver);
};

CollisionResults SimpleAABBtoCircle(AABB box, Circle circ)
{
	int NearestX = Max(box.Left(), Min(circ._X, box.Right()));
	int NearestY = Max(box.Top(), Min(circ._Y, box.Bottom()));

	float Distance = CalcDistance(NearestX, NearestY, circ._X, circ._Y);

	if (Distance > circ._Radius)
		return CollisionResults(false);
	PairFloat sepVec(NearestX - circ._X, NearestY - circ._Y);
	return CollisionResults(true, sepVec);
};

CollisionResults SATCheckAABBtoCircle(AABB box, Circle circ)
{
	//	Based on: http://www.dyn4j.org/2010/01/sat/#sat-mtv
		
	std::vector<Point> v1 = GenVertices(box);
	Point closestVert = v1[0];

	std::vector<Vec> axes = GenAABBNormals();

	Vec minAxis = axes[0];
	float minOver = 1000000.f;

	for (int i = 0; i < (int)axes.size(); i++)
	{
		PairFloat p1 = Project(v1, axes[i]);
		PairFloat p2 = Project(circ, axes[i]);

		if (!Overlaps(p1, p2))
			return CollisionResults(false);

		if (Abs(CalcOverlap(p1, p2)) < minOver)
		{
			minOver = CalcOverlap(p1, p2);
			minAxis = axes[i];
		}

		if (CalcDistance((float)v1[i].getX(), (float)v1[i].getY(), (float)circ._X, (float)circ._Y) < CalcDistance((float)closestVert.getX(), (float)closestVert.getY(), (float)circ._X, (float)circ._Y))
			closestVert = v1[i];
	}

	Vec closestAxe((float)(circ._X - closestVert.getX()), (float)(circ._Y - closestVert.getY()));

	//	Final check against axis between circle center and closest AABB vertex
	PairFloat p1 = Project(v1, closestAxe);
	PairFloat p2 = Project(circ, closestAxe);

	if (!Overlaps(p1, p2))
		return CollisionResults(false);

	if (CalcOverlap(p1, p2) < minOver)
	{
		minOver = CalcOverlap(p1, p2);
		minAxis = closestAxe;
	}

	return CollisionResults(true, minAxis.UnitVec() * minOver);
};