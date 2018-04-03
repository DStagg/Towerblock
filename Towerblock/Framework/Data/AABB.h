#ifndef AABB_H
#define AABB_H

class AABB
{
public:

	AABB();
	AABB(int x, int y, int w, int h);	//	Defines an axis-aligned bounding box with top-left (x,y) and dimensions (w,h)
	~AABB();

	int Left();
	int Right();
	int Top();
	int Bottom();

	int _X, _Y, _Width, _Height;

	bool Contains(int x, int y);
	bool Intersects(AABB box);
};

#endif