#include "Pickup.h"

Pickup::Pickup()
{

};
Pickup::~Pickup()
{

};

void Pickup::Input()
{

};
void Pickup::Update(float dt)
{

};
void Pickup::Draw(sf::RenderWindow* rw)
{

};

CircleMask Pickup::GetMask()
{
	return CircleMask(Circle(_Position.GetX(), _Position.GetY(), 10));
};