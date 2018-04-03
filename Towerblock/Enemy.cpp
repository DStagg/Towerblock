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

	_Mask._Mask = Circle((float)_Position.getX(), (float)_Position.getY(), 16.f);
};

void Enemy::Draw(sf::RenderWindow* rw)
{
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Green);
	circ.setRadius(((float)_Size._X + (float)_Size._Y) / 4.f);
	circ.setPosition((float)_Position.getX(), (float)_Position.getY());
	rw->draw(circ);
};

CircleMask& Enemy::GetMask()
{
	return _Mask;
};