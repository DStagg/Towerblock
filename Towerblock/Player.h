#ifndef PLAYER_H
#define PLAYER_H

#include "Console.h"
#include "Framework\Utility\Utility.h"

#include "Framework\Entities\Entity.h"
#include "Rotation.h"

class Player : public Entity
{
public:

	Player();
	~Player();

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	void Knockback(PairFloat over = PairFloat(0.f, 0.f));

	CircleMask& GetMask();

private:

	float _KnockbackTimer = 0.f;
	CircleMask _Mask;
};

#endif