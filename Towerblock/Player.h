#ifndef PLAYER_H
#define PLAYER_H

#include "Framework\Entities\Entity.h"
#include "Rotation.h"

class Player : public Entity
{
public:

	Player();
	~Player();

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);
	AABB GenAABB();

	void Knockback();

private:

	float _KnockbackTimer = 0.f;

};

#endif