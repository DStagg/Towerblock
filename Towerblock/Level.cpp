#include "Level.h"

/////

Tile::Tile(int str_id, bool s)
{
	_SpriteID = str_id;
	_Solid = s;
};

/////

Level::Level()
{

};

Level::~Level()
{

};

void Level::GenerateBox(int w, int h)
{
	if (w < 3) w = 3;
	if (h < 3) h = 3;

	_Tiles.Resize(w, h);
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
		{
			if ((x == 0) || (x == w - 1)) _Tiles.SetCell(x, y, 1);
			else if ((y == 0) || (y == h - 1)) _Tiles.SetCell(x, y, 1);
			else _Tiles.SetCell(x, y, 0);
		}

	_TileTypes[0] = Tile(0, false);
	_TileTypes[1] = Tile(1, true);
};

Grid& Level::GetGrid()
{
	return _Tiles;
};

std::map<int, Tile> Level::GetTileTypes()
{
	return _TileTypes;
};

bool Level::IsSolid(int x, int y)
{
	if ((x < 0) || (y < 0) || (x >= _Tiles.GetWidth()) || (y >= _Tiles.GetHeight())) return false;
	return _TileTypes[_Tiles.GetCell(x, y)]._Solid;
};

int Level::CalcCol(float x)
{
	return ((int)x - ( (int)x % _TileWidth)) / _TileWidth;
};

int Level::CalcRow(float y)
{
	return ((int)y - ((int)y % _TileHeight)) / _TileHeight;
};

CollisionResults Level::WallCollision(AABBMask mask)
{
	int lCol = CalcCol((float)mask._Mask._X);
	int rCol = CalcCol((float)mask._Mask.Right());
	int tRow = CalcCol((float)mask._Mask._Y);
	int bRow = CalcRow((float)mask._Mask.Bottom());

	for (int x = lCol; x <= rCol; x++)
		for (int y = tRow; y <= bRow; y++)
		{
			if (IsSolid(x, y))
			{
				return CollisionResults(true);	//	TODO: need to fill in rest of CollisionResults (axis & overlap)
			}
		}

	return CollisionResults();
};

CollisionResults Level::WallCollision(CircleMask mask)
{
	int lCol = CalcCol((mask._Mask._X - mask._Mask._Radius) + 1.f);
	int rCol = CalcCol((mask._Mask._X + mask._Mask._Radius) - 1.f);
	int tRow = CalcCol((mask._Mask._Y - mask._Mask._Radius) + 1.f);
	int bRow = CalcRow((mask._Mask._Y + mask._Mask._Radius) - 1.f);

	for (int x = lCol; x <= rCol; x++)
		for (int y = tRow; y <= bRow; y++)
		{
			if (IsSolid(x, y))
			{
				AABB box(x * _TileWidth, y * _TileHeight, _TileWidth, _TileHeight);
				if (CollideCircletoAABB(mask._Mask, box)._Collided)
					return CollisionResults(true);	//	TODO: need to fill in rest of CollisionResults (axis & overlap)
			}
		}

	return CollisionResults();
};