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
	sf::CircleShape circ;
	circ.setPosition((float)_Position.GetX(), (float)_Position.GetY());
	circ.setRadius(10.f);
	circ.setFillColor(sf::Color(155,155,155));
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	rw->draw(circ);
};

CircleMask Pickup::GetMask()
{
	return CircleMask(Circle(_Position.GetX(), _Position.GetY(), 10));
};