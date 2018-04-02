#include "Enemy.h"

Enemy::Enemy()
{
	_Size = PairFloat(32.f, 32.f);
};

Enemy::~Enemy()
{

};

void Enemy::Update(float dt)
{
	_Position._X += _Velocity._X * dt;
	_Position._Y += _Velocity._Y * dt;

	_Mask._Mask = Circle(_Position._X, _Position._Y, 16.f);
};

void Enemy::Draw(sf::RenderWindow* rw)
{
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Green);
	circ.setRadius(((float)_Size._X + (float)_Size._Y) / 4.f);
	circ.setPosition(_Position._X, _Position._Y);
	rw->draw(circ);
};

CircleMask& Enemy::GetMask()
{
	return _Mask;
};