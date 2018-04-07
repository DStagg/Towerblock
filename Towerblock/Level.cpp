#include "Level.h"

/////

Tile::Tile(int str_id, bool s)
{
	_SpriteID = str_id;
	_Solid = s;
};

/////

Impulse::Impulse(Entity* e, float time, Vec accel)
{
	_Target = e;
	_TimeRemaining = time;
	_TimeLength = time;
	_Accel = accel;
};

/////

Level::Level()
{
	_Player._Position.Set(200, 200);

	Pickup p;
	p._Position.Set(150, 100);
	_Pickups.push_back(p);
	p._Position.Set(500, 500);
	_Pickups.push_back(p);

	_GunA = new Pistol();
	_GunB = new Shotgun();
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

void Level::GenerateFancyBox(int w, int h)
{
	if (w < 3) w = 3;
	if (h < 3) h = 3;

	_Tiles.Resize(w, h);
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if (x == 0) _Tiles.SetCell(x, y, 4);			//	L
			else if (x == w - 1) _Tiles.SetCell(x, y, 6);	//	R
			else if (y == 0) _Tiles.SetCell(x, y, 2);		//	T
			else if (y == h - 1) _Tiles.SetCell(x, y, 8);	//	B
			else _Tiles.SetCell(x, y, 5);					//	Mid
		}
	}
	_Tiles.SetCell(0, 0, 1);			//	TL
	_Tiles.SetCell(w - 1, 0, 3);		//	TR
	_Tiles.SetCell(0, h - 1, 7);		//	BL
	_Tiles.SetCell(w - 1, h - 1, 9);	//	BR
	
	_TileTypes[0] = Tile(0, false);
	_TileTypes[1] = Tile(4, true);	//	TL
	_TileTypes[2] = Tile(8, true);	//	T
	_TileTypes[3] = Tile(6, true);	//	TR
	_TileTypes[4] = Tile(5, true);	//	L
	_TileTypes[5] = Tile(13, true);	//	Mid
	_TileTypes[6] = Tile(7, true);	//	R
	_TileTypes[7] = Tile(9, true);	//	BL
	_TileTypes[8] = Tile(10, true);	//	B
	_TileTypes[9] = Tile(11, false);//	BR
	
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

void Level::Spawn(int x, int y)
{
	Enemy temp;
	temp._Position.Set(x, y);
	temp._Velocity = Vec((float)Random::R()->Generate(-70, 70), (float)Random::R()->Generate(-70, 70));
	_Enemies.push_back(temp);
};
void Level::Spawn(int x, int y, int vx, int vy)
{
	Enemy temp;
	temp._Position.Set(x, y);
	temp._Velocity = Vec((float)vx, (float)vy);
	_Enemies.push_back(temp);
};

void Level::Update(float dt, sf::RenderWindow* rw)
{
	if (_FireTimer > 0.f)
		_FireTimer -= dt;
	if (_FlashTimer > 0.f)
		_FlashTimer -= dt;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _FireTimer <= 0.f)
	{
		_FireTimer = _GunA->_Cooldown;

		Vec firePos = _Player._Position + (Vec(CalcXComp(_Player._Facing), CalcYComp(_Player._Facing)).UnitVec() * 50.f);
		std::vector<Bullet> newB = _GunA->Fire((int)firePos._X, (int)firePos._Y, _Player._Facing);

		for (int i = 0; i < (int)newB.size(); i++)
			_Bullets.push_back(newB[i]);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && _FireTimer <= 0.f)
	{
		_FireTimer = _GunB->_Cooldown;

		Vec firePos = _Player._Position + (Vec(CalcXComp(_Player._Facing), CalcYComp(_Player._Facing)).UnitVec() * 50.f);
		std::vector<Bullet> newB = _GunB->Fire((int)firePos._X, (int)firePos._Y, _Player._Facing);

		for (int i = 0; i < (int)newB.size(); i++)
			_Bullets.push_back(newB[i]);
	}

	//	Input
	_Player._Facing = CalcHeading((float)_Player._Position.GetX(), (float)_Player._Position.GetY(), (float)sf::Mouse::getPosition(*rw).x, (float)sf::Mouse::getPosition(*rw).y);
	_Player.Input();
	for (int i = 0; i < (int)_Enemies.size(); i++)
		_Enemies[i].Input();
	for (int i = 0; i < (int)_Bullets.size(); i++)
		_Bullets[i].Input();

	//	HACK: get the 1st enemy to chase the player
	if ((int)_Enemies.size() > 0)
		_Enemies[0]._Velocity = Vec(_Enemies[0]._Position - _Player._Position).UnitVec() * -100.f;

	//	Impulses
	for (int i = 0; i < (int)_Impulses.size(); i++)
	{
		_Impulses[i]._Target->_Velocity += _Impulses[i]._Accel;
		_Impulses[i]._TimeRemaining -= dt;
		if (_Impulses[i]._TimeRemaining <= 0.f)
		{
			_Impulses.erase(_Impulses.begin() + i);
			i--;
		}
	}

	//	Collide
	CollisionResults pres = WallCollision(_Player.GetMask());
	if (pres._Collided)
	{
		_Player._Velocity = Vec(0.f, 0.f);
		_Player._Position += pres._Overlap;
	}

	for (int i = 0; i < (int)_Pickups.size(); i++)
	{
		if (_Pickups[i]._Alive && _Player.GetMask().Collide(_Pickups[i].GetMask())._Collided)
		{
			GetGun(0)->_CurrentAmmo = GetGun(0)->_MaxAmmo;
			GetGun(1)->_CurrentAmmo = GetGun(1)->_MaxAmmo;
			_Pickups[i]._Alive = false;
		}
	}

	for (int i = 0; i < (int)_Enemies.size(); i++)
	{
		//	Kill the Enemy if it gets off the screen
		if (!AABB(0, 0, rw->getSize().x, rw->getSize().y).Contains(_Enemies[i]._Position.GetX(), _Enemies[i]._Position.GetY()))
		{
			_Enemies[i]._Alive = false;
			continue;					//	If the enemy is now dead for being off screen no point doing collisions checks.
		}

		//	Collide the Enemy against the Walls
		CollisionResults wres = WallCollision(_Enemies[i].GetMask());
		if (wres._Collided)
		{
			_Enemies[i]._Position += wres._Overlap;
			_Enemies[i]._Velocity *= -1;
		}

		//	Collide the Enemy against the Player
		CollisionResults res = _Enemies[i].GetMask().Collide(_Player.GetMask());
		if (res._Collided)
		{
			//	Need to make sure we are not pushing the player inside of a wall
			CircleMask projected = _Player.GetMask();
			projected._Mask._X -= (int)res._Overlap._X;
			projected._Mask._Y -= (int)res._Overlap._Y;
			CollisionResults res2 = WallCollision(projected);

			if (res2._Collided)	//	If knocking the player back would intersect a wall, just move them TO the wall and deal damage
			{
				_Player._Position.Set(projected._Mask._X + res2._Overlap._X, projected._Mask._Y + res2._Overlap._Y);
				if (_Player.Knockback()) _FlashTimer = _FlashDuration;
			}
			else	//	Otherwise, separate them from the enemy and apply a knockback force
			{
				if (_Player.Knockback(res._Overlap)) _FlashTimer = _FlashDuration;
				_Impulses.push_back(Impulse(&_Player, 0.1f, res._Overlap.UnitVec() * -200.f));
				_Impulses.push_back(Impulse(&_Enemies[i], 0.1f, res._Overlap.UnitVec() * 200.f));
			}
			_Enemies[i]._Position += res._Overlap;	//	Either way, move the enemy back from the player so there is no overlap
		}
	}
	
	for (int i = 0; i < (int)_Bullets.size(); i++)
	{
		if (!AABB(0, 0, rw->getSize().x, rw->getSize().y).Contains(_Bullets[i]._Position.GetX(), _Bullets[i]._Position.GetY()))
			_Bullets[i]._Alive = false;

		if (_Bullets[i]._Alive && WallCollision(_Bullets[i].GetMask())._Collided)	//	No point doing a wall check for dead ones
			_Bullets[i]._Alive = false;

		for (int e = 0; e < (int)_Enemies.size(); e++)
			if (_Bullets[i].GetMask().Collide(_Enemies[e].GetMask())._Collided)
			{
				_Bullets[i]._Alive = false;
				_Enemies[e]._Alive = false;
			}
	}
	
	//	Update Position/etc.
	_Player.Update(dt);
	for (int i = 0; i < (int)_Enemies.size(); i++)
		_Enemies[i].Update(dt);
	for (int i = 0; i < (int)_Bullets.size(); i++)
		_Bullets[i].Update(dt);
	for (int i = 0; i < (int)_Pickups.size(); i++)
		_Pickups[i].Update(dt);

	//	Resolve/Cull
	for (int i = 0; i < (int)_Enemies.size(); i++)
	{
		if (!_Enemies[i]._Alive)
		{
			_Enemies.erase(_Enemies.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < (int)_Bullets.size(); i++)
	{
		if (!_Bullets[i]._Alive)
		{
			_Bullets.erase(_Bullets.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < (int)_Pickups.size(); i++)
	{
		if (!_Pickups[i]._Alive)
		{
			_Pickups.erase(_Pickups.begin() + i);
			i--;
		}
	}
};

void Level::Draw(sf::RenderWindow* rw)
{
	for (int i = 0; i < (int)_Pickups.size(); i++)
	{
		_Pickups[i].Draw(rw);
	}
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

float Level::GetFlashTimer()
{
	return _FlashTimer;
};

float Level::GetFlashDuration()
{
	return _FlashDuration;
};

int Level::CountEnemies()
{
	return (int)_Enemies.size();
};

Gun* Level::GetGun(int i)
{
	if (i == 0)
		return _GunA;
	else
		return _GunB;
};