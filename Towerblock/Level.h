#ifndef LEVEL_H
#define LEVEL_H

#include "Framework\Data\Grid.h"
#include <map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

#include "Framework\Data\Collision.h"

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

	Grid& GetGrid();
	std::map<int, Tile> GetTileTypes();

	bool IsSolid(int x, int y);
	int CalcCol(float x);
	int CalcRow(float y);

	CollisionResults WallCollision(AABBMask mask);
	CollisionResults WallCollision(CircleMask mask);

	void Fire();
	void Update(float dt, sf::RenderWindow* rw);
	void Draw(sf::RenderWindow* rw);

private:

	Grid _Tiles;
	std::map<int, Tile> _TileTypes;

	int _TileWidth = 32;
	int _TileHeight = 32;

	float _FireTimer = 0.f;

	Player _Player;
	std::vector<Enemy> _Enemies;
	std::vector<Bullet> _Bullets;
};

#endif