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
};

void Enemy::Draw(sf::RenderWindow* rw)
{
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Green);
	circ.setRadius(((float)_Size._X + (float)_Size._Y) / 4.f);
	circ.setPosition(_Position._X, _Position._Y);
	rw->draw(circ);
};

AABB Enemy::GenAABB()
{
	return AABB(_Position._X, _Position._Y, _Size._X, _Size._Y);
};