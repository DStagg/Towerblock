#include "Enemy.h"

Enemy::Enemy()
{
	_Size = PairInt(32, 32);
};

Enemy::~Enemy()
{

};

void Enemy::Update(float dt)
{
	_Position += _Velocity * dt;

	_Mask._Mask = Circle(_Position.GetX(), _Position.GetY(), 16);
};

void Enemy::Draw(sf::RenderWindow* rw)
{
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Green);
	circ.setRadius(((float)_Size._B + (float)_Size._B) / 4.f);
	circ.setPosition((float)_Position.GetX(), (float)_Position.GetY());
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	rw->draw(circ);
};

CircleMask& Enemy::GetMask()
{
	return _Mask;
};