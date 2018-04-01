#ifndef PLAYER_H
#define PLAYER_H

#include "Framework\Entities\Entity.h"

class Player : public Entity
{
public:

	Player();
	~Player();

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);
	AABB GenAABB();

private:



};

#endif