#include "Enemy.h"

Enemy::Enemy()
{
	_Size = PairInt(32, 32);
};

Enemy::~Enemy()
{

};

void Enemy::Input()
{

};

void Enemy::Update(float dt)
{
	Entity::Update(dt);

	_Facing = CalcHeading(_Velocity._X, _Velocity._Y);
};

void Enemy::Draw(sf::RenderWindow* rw)
{
	//	Draw main body
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Green);
	circ.setRadius(16.f);
	circ.setOrigin(16.f, 16.f);
	circ.setPosition((float)_Position.GetX(), (float)_Position.GetY());
	rw->draw(circ);

	//	Indicate facing
	sf::CircleShape circ2;
	circ2.setRadius(2.5f);
	circ2.setFillColor(sf::Color::Green);
	circ2.setOrigin(2.5f, 2.5f);
	circ2.setPosition(_Position.GetX() + (32.f * CalcXComp(_Facing)), _Position.GetY() + (32.f * CalcYComp(_Facing)));
	rw->draw(circ2);
};

CircleMask Enemy::GetMask()
{
	return CircleMask(Circle(_Position.GetX(), _Position.GetY(), 16));
};