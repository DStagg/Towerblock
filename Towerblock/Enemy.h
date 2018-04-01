#ifndef ENEMY_H
#define ENEMY_H

#include "Framework\Entities\Entity.h"

class Enemy : public Entity
{
public:
	
	Enemy();
	~Enemy();

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);
	AABB GenAABB();
	
private:


};

#endif