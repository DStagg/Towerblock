#ifndef LEVEL_H
#define LEVEL_H

#include "Framework\Data\Grid.h"
#include <map>

#include "Player.h"

#include "Collision.h"

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
	CollisionResults WallCollision(AABBMask mask);
	CollisionResults WallCollision(CircleMask mask);

private:

	Grid _Tiles;
	std::map<int, Tile> _TileTypes;

	int _TileWidth = 32;
	int _TileHeight = 32;
};

#endif