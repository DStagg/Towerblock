#ifndef LEVEL_H
#define LEVEL_H

#include "Framework\Data\Grid.h"
#include <map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Pickup.h"

#include "Framework\IO\BinarySave.h"

#include "Framework\Data\Collision.h"
#include "Framework\Debug\DebugDraw.h"

#include "Framework\Utility\Random.h"

#include "Gun.h"

struct Tile
{
	Tile(int sprx = 0, int spry = 0, bool solid = false);
	int _SpriteX, _SpriteY;
	bool _Solid;
};

struct Impulse
{
	Impulse(Entity* e = 0, float time = 0.f, Vec accel = Vec());
	Entity* _Target;
	float _TimeLength, _TimeRemaining;
	Vec _Accel;
};

class Level
{
public:

	Level();
	~Level();

	void GenerateBox(int w, int h);
	void GenerateFancyBox(int w, int h);

	Grid<Tile>& GetGrid();
	Grid<PairInt> BuildSpriteCoordGrid();

	bool IsSolid(int x, int y);
	int CalcCol(float x);
	int CalcRow(float y);
	//	TODO: Change WallCollision tests to take into account velocity and dt?
	//	TODO: May also help to get wall collision working better by checkng each axis one at a time, etc.
	CollisionResults WallCollision(AABBMask mask);
	CollisionResults WallCollision(CircleMask mask);

	void Spawn(int x, int y);
	void Spawn(int x, int y, int velx, int vely);
	void Update(float dt, sf::RenderWindow* rw);
	void Draw(sf::RenderWindow* rw);

	Player& GetPlayer();

	float GetFireTimer();

	float GetFlashTimer();
	float GetFlashDuration();

	int CountEnemies();
	Gun* GetGun(int i);

	void Load(std::string file);
	void Save(std::string file);

private:

	Grid<Tile> _Tiles;

	int _TileWidth = 32;
	int _TileHeight = 32;

	float _FireTimer = 0.f;
	float _FlashTimer = 0.f;
	float _FlashDuration = 0.1f;

	Gun* _GunA;
	Gun* _GunB;

	Player _Player;
	PairInt _PlayerStartPos;
	std::vector<Enemy> _Enemies;
	std::vector<Bullet> _Bullets;
	std::vector<Pickup> _Pickups;

	std::vector<Impulse> _Impulses;
};

/*	Level Save Format
	int Width
	int Height
	Tiles: X by Y:
		int SpriteX
		int SpriteY
		bool Solid
	int PlayerStartX
	int PlayerStartY
	int NumberOfEnemies
	Enemies: by int id:
		int StartX
		int StartY
		float StartXVel
		float StartYVel
	int NumberOfPickups
	Pickups: by int id:
		int PositionX
		int PositionY
*/
#endif