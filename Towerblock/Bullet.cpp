#include "Bullet.h"

Bullet::Bullet()
{
	_Size = PairInt(8, 8);
};
Bullet::~Bullet()
{

};

void Bullet::Update(float dt)
{
	_Position += _Velocity * dt;
	
	_Mask._Mask = Circle(_Position.GetX(), _Position.GetY(), 8);
};

void Bullet::Draw(sf::RenderWindow* rw)
{
	sf::CircleShape circ;
	circ.setPosition((float)_Position.GetX(), (float)_Position.GetY());
	circ.setRadius((float)(_Size._A + _Size._B) / 2.f);
	circ.setFillColor(sf::Color::Yellow);
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	rw->draw(circ);
};

CircleMask& Bullet::GetMask()
{
	return _Mask;
};