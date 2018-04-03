#include "Bullet.h"

Bullet::Bullet()
{
	_Size = PairInt(16, 16);
};
Bullet::~Bullet()
{

};

void Bullet::Update(float dt)
{
	_Position += _Velocity * dt;
	
	_Mask._Mask = Circle(_Position.getX(), _Position.getY(), 16);
};

void Bullet::Draw(sf::RenderWindow* rw)
{
	sf::RectangleShape rect;
	rect.setPosition((float)_Position.getX(), (float)_Position.getY());
	rect.setSize(sf::Vector2f((float)_Size._X, (float)_Size._Y));
	rect.setFillColor(sf::Color::Yellow);
	rw->draw(rect);
};

CircleMask& Bullet::GetMask()
{
	return _Mask;
};