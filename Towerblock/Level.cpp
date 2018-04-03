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
	_Player._Position.set(200, 200);
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

	return CollisionResults(false);
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

	return CollisionResults(false);
};

//	HACK: need to get wall collision working better e.g. by checkng each axis one at a time, etc.

void Level::Fire()
{
	if (_FireTimer > 0.f)
		return;
	_FireTimer = 0.2f;

	Bullet temp;
	temp._Position.set(_Player._Position.getX(), _Player._Position.getY());
	temp._Velocity = Vec(CalcXComp(_Player._Facing), CalcYComp(_Player._Facing)).UnitVec() * 100.f;
	temp._Position += temp._Velocity.UnitVec() * 50;
	_Bullets.push_back(temp);
};

void Level::Update(float dt)
{
	if (_FireTimer > 0.f)
		_FireTimer -= dt;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		Fire();

	_Player.Update(dt);

	for (int i = 0; i < (int)_Bullets.size(); i++)
		_Bullets[i].Update(dt);
};

void Level::Draw(sf::RenderWindow* rw)
{
	_Player.Draw(rw);

	for (int i = 0; i < (int)_Bullets.size(); i++)
		_Bullets[i].Draw(rw);
};