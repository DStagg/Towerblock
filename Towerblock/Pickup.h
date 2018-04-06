#ifndef PICKUP_H
#define PICKUP_H

#include "Framework\Entities\Entity.h"

class Pickup : public Entity
{
public:

	Pickup();
	~Pickup();

	void Input();
	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	CircleMask GetMask();

private:

};

#endif