#ifndef BULLET_H
#define BULLET_H

#include "Framework\Entities\Entity.h"

class Bullet : public Entity
{
public:

	Bullet();
	~Bullet();

	void Input();
	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	CircleMask GetMask();

private:

};

#endif