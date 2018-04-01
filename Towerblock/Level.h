#ifndef LEVEL_H
#define LEVEL_H

#include "Framework\Data\Grid.h"
#include <map>

#include "Player.h"

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

struct Tile
{
	Tile(int spr_id = 0, bool solid = false);
	int _SpriteID;
	bool _Solid;
};

class Level
{
public:

	Level();
	~Level();

	void GenerateBox(int w, int h);

	Grid GetGrid();
	std::map<int, Tile> GetTileTypes();

	bool IsSolid(int x, int y);
	int CalcCol(float x);
	int CalcRow(float y);

	CollisionResults WallCollision(Entity* ent);

private:

	Grid _Tiles;
	std::map<int, Tile> _TileTypes;

	int _TileWidth = 32;
	int _TileHeight = 32;
};

#endif