#ifndef ENTITY_H
#define ENTITY_H

#include "../Data/AABB.h"
#include "../Data/Pair.h"
#include "SFML\Graphics.hpp"

#include "../../Collision.h"

class Entity
{
public:

	Entity();
	~Entity();

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* rw) = 0;

	bool _Alive = true;

	PairFloat	_Position = PairFloat(0.f,0.f);
	PairFloat	_Velocity = PairFloat(0.f, 0.f);
	PairFloat	_Size = PairFloat(0.f, 0.f);

	float _Facing = 0.f;

	int _HP = 100;

};

#endif