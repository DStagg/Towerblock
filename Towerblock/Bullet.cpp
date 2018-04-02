#include "Bullet.h"

Bullet::Bullet()
{
	_Size = PairFloat(16.f, 16.f);
};
Bullet::~Bullet()
{

};

void Bullet::Update(float dt)
{
	_Position._X += _Velocity._X * dt;
	_Position._Y += _Velocity._Y * dt;
};

void Bullet::Draw(sf::RenderWindow* rw)
{
	sf::RectangleShape rect;
	rect.setPosition(_Position._X, _Position._Y);
	rect.setSize(sf::Vector2f(_Size._X, _Size._Y));
	rect.setFillColor(sf::Color::Yellow);
	rw->draw(rect);
};

AABB Bullet::GenAABB()
{
	return AABB(_Position._X, _Position._Y, _Size._X, _Size._Y);
};