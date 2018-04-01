#ifndef LEVEL_H
#define LEVEL_H

#include "Framework\Data\Grid.h"
#include <map>

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

private:

	Grid _Tiles;
	std::map<int, Tile> _TileTypes;

};

#endif