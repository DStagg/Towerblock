#ifndef PLAYER_H
#define PLAYER_H

#include "Framework\Debug\Console.h"
#include "Framework\Utility\Utility.h"

#include "Framework\Entities\Entity.h"

class Player : public Entity
{
public:

	Player();
	~Player();

	void Input();
	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	void Knockback(Vec over = Vec(0.f, 0.f));

	CircleMask GetMask();

private:

	float _KnockbackTimer = 0.f;
	CircleMask _Mask;
};

#endif