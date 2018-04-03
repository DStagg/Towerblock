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
	
	_Mask._Mask = Circle(_Position.getX(), _Position.getY(), 8);
};

void Bullet::Draw(sf::RenderWindow* rw)
{
	sf::CircleShape circ;
	circ.setPosition((float)_Position.getX(), (float)_Position.getY());
	circ.setRadius((float)(_Size._X + _Size._Y) / 2.f);
	circ.setFillColor(sf::Color::Yellow);
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	rw->draw(circ);
};

CircleMask& Bullet::GetMask()
{
	return _Mask;
};