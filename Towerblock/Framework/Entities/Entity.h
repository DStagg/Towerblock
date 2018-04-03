#ifndef ENTITY_H
#define ENTITY_H

#include "../Data/AABB.h"
#include "../Data/Pair.h"
#include "SFML\Graphics.hpp"
#include "../../Vector.h"
#include "../../Point.h"
#include "../../Collision.h"

class Entity
{
public:

	Entity();
	~Entity();

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* rw) = 0;

	bool _Alive = true;

	Point	_Position = Point(0, 0);
	Vec	_Velocity = Vec(0.f, 0.f);
	PairInt	_Size = PairInt(0, 0);

	float _Facing = 0.f;

	int _HP = 100;

};

#endif