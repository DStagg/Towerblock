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
	_Position += _Velocity * dt;
	
	_Mask._Mask = Circle(_Position._X, _Position._Y, 16.f);
};

void Bullet::Draw(sf::RenderWindow* rw)
{
	sf::RectangleShape rect;
	rect.setPosition(_Position._X, _Position._Y);
	rect.setSize(sf::Vector2f(_Size._X, _Size._Y));
	rect.setFillColor(sf::Color::Yellow);
	rw->draw(rect);
};

CircleMask& Bullet::GetMask()
{
	return _Mask;
};