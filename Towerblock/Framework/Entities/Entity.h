#ifndef ENTITY_H
#define ENTITY_H

#include "../Data/AABB.h"
#include "../Data/Pair.h"
#include "SFML\Graphics.hpp"
#include "../../Vector.h"
#include "../../Collision.h"

class Entity
{
public:

	Entity();
	~Entity();

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* rw) = 0;

	bool _Alive = true;

	Vec	_Position = Vec(0.f, 0.f);
	Vec	_Velocity = Vec(0.f, 0.f);
	PairFloat	_Size = PairFloat(0.f, 0.f);

	float _Facing = 0.f;

	int _HP = 100;

};

#endif