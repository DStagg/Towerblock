#ifndef ENTITY_H
#define ENTITY_H

#include "../Data/AABB.h"
#include "../Data/Pair.h"
#include "SFML\Graphics.hpp"

class Entity
{
public:

	Entity();
	~Entity();

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* rw) = 0;

	bool _Alive;

	PairFloat	_Position;
	PairFloat	_Velocity;
	PairFloat	_Size;

};


#endif