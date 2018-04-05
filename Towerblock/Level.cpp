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
	_Player._Position.Set(200, 200);
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
				AABBMask temp(AABB(x * _TileWidth, y * _TileHeight, _TileWidth, _TileHeight));
				CollisionResults res = mask.Collide(temp);
				if (!res._Collided)	Log("WallCollision(AABB) discrepancy: mask check not returning true.");
				return res;
			}
		}

	return CollisionResults(false, Vec());
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
				AABBMask box(AABB(x * _TileWidth, y * _TileHeight, _TileWidth, _TileHeight));
				CollisionResults res = mask.Collide(box);
				if (res._Collided)
					return res;
			}
		}

	return CollisionResults(false, Vec());
};

void Level::Fire()
{
	if (_FireTimer > 0.f)
		return;
	_FireTimer = 0.2f;

	Bullet temp;
	temp._Position.Set(_Player._Position.GetX(), _Player._Position.GetY());
	temp._Velocity = Vec(CalcXComp(_Player._Facing), CalcYComp(_Player._Facing)).UnitVec() * 100.f;
	temp._Position += temp._Velocity.UnitVec() * 50;
	_Bullets.push_back(temp);
};

void Level::FireShotgun()
{
	if (_FireTimer > 0.f)
		return;
	_FireTimer = 0.5f;

	Bullet temp;
	temp._Position.Set(_Player._Position.GetX(), _Player._Position.GetY());
	temp._Velocity = Vec(CalcXComp(_Player._Facing), CalcYComp(_Player._Facing)).UnitVec() * 100.f;
	temp._Position += temp._Velocity.UnitVec() * 50;
	_Bullets.push_back(temp);

	float spread = DegreeToRad(45.f);

	temp._Velocity = Vec(CalcXComp(_Player._Facing - spread), CalcYComp(_Player._Facing - spread)).UnitVec() * 100.f;
	_Bullets.push_back(temp);

	temp._Velocity = Vec(CalcXComp(_Player._Facing + spread), CalcYComp(_Player._Facing + spread)).UnitVec() * 100.f;
	_Bullets.push_back(temp);

	temp._Velocity = Vec(CalcXComp(_Player._Facing - spread / 2.f), CalcYComp(_Player._Facing - spread / 2.f)).UnitVec() * 100.f;
	_Bullets.push_back(temp);

	temp._Velocity = Vec(CalcXComp(_Player._Facing + spread / 2.f), CalcYComp(_Player._Facing + spread / 2.f)).UnitVec() * 100.f;
	_Bullets.push_back(temp);
};

void Level::Spawn(int x, int y)
{
	Enemy temp;
	temp._Position.Set(x, y);
	temp._Velocity = Vec((float)Random::R()->Generate(-70, 70), (float)Random::R()->Generate(-70, 70));
	_Enemies.push_back(temp);
};

void Level::Update(float dt, sf::RenderWindow* rw)
{
	if (_FireTimer > 0.f)
		_FireTimer -= dt;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		Fire();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		FireShotgun();

	_Player._Facing = CalcHeading((float)_Player._Position.GetX(), (float)_Player._Position.GetY(), (float)sf::Mouse::getPosition(*rw).x, (float)sf::Mouse::getPosition(*rw).y);
	_Player.Update(dt);

	CollisionResults pres = WallCollision(_Player.GetMask());
	if (pres._Collided)
	{
		_Player._Velocity = Vec(0.f, 0.f);
		
		_Player._Position += pres._Overlap;

		Log("Collision: After [" + FloatToString(pres._Overlap._X) + "," + FloatToString(pres._Overlap._Y) + "] Player now at (" + IntToString(_Player._Position.GetX()) + "," + IntToString(_Player._Position.GetY()) + ")");
	}

	//	Bullet update loop
	for (int i = 0; i < (int)_Bullets.size(); i++)
	{
		_Bullets[i].Update(dt);

		for (int e = 0; e < (int)_Enemies.size(); e++)
			if (_Bullets[i].GetMask().Collide(_Enemies[e].GetMask())._Collided)
			{
				_Bullets[i]._Alive = false;
				_Enemies[e]._Alive = false;
			}

		if (WallCollision(_Bullets[i].GetMask())._Collided)
			_Bullets[i]._Alive = false;

		if (!AABB(0, 0, rw->getSize().x, rw->getSize().y).Contains(_Bullets[i]._Position.GetX(), _Bullets[i]._Position.GetY()))
			_Bullets[i]._Alive = false;

		if (!_Bullets[i]._Alive)
		{
			_Bullets.erase(_Bullets.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < (int)_Enemies.size(); i++)
	{
		_Enemies[i].Update(dt);

		CollisionResults res = _Enemies[i].GetMask().Collide(_Player.GetMask());
		if (res._Collided)
		{
			_Player.Knockback(res._Overlap);
			_Enemies[i]._Position -= _Enemies[i]._Velocity * dt;
		}
		
		CollisionResults wres = WallCollision(_Enemies[i].GetMask());
		if (wres._Collided)
		{
			_Enemies[i]._Position += wres._Overlap;
			_Enemies[i]._Velocity *= -1;
		}

		if (!AABB(0, 0, rw->getSize().x, rw->getSize().y).Contains(_Enemies[i]._Position.GetX(), _Enemies[i]._Position.GetY()))
			_Enemies[i]._Alive = false;

		if (!_Enemies[i]._Alive)
		{
			_Enemies.erase(_Enemies.begin() + i);
			i--;
		}
	}
};

void Level::Draw(sf::RenderWindow* rw)
{
	for (int i = 0; i < (int)_Enemies.size(); i++)
	{
		_Enemies[i].Draw(rw);
	//	DebugDrawMask(_Enemies[i].GetMask(), rw);
	}

	for (int i = 0; i < (int)_Bullets.size(); i++)
	{
		_Bullets[i].Draw(rw);
	//	DebugDrawMask(_Bullets[i].GetMask(), rw);
	}

	_Player.Draw(rw);
	//DebugDrawMask(_Player.GetMask(), rw);
};

Player& Level::GetPlayer()
{
	return _Player;
};

float Level::GetFireTimer()
{
	return _FireTimer;
};