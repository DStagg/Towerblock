#include "Player.h"

Player::Player()
{
	_Size = PairFloat(32.f, 32.f);
};

Player::~Player()
{

};

void Player::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		_Velocity._Y = -100.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		_Velocity._Y = 100.f;
	else
		_Velocity._Y = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		_Velocity._X = -100.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		_Velocity._X = 100.f;
	else
		_Velocity._X = 0.f;

	_Position._X += _Velocity._X * dt;
	_Position._Y += _Velocity._Y * dt;
};

void Player::Draw(sf::RenderWindow* rw)
{
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Blue);
	circ.setRadius(((float)_Size._X + (float)_Size._Y) / 4.f);
	circ.setPosition(_Position._X, _Position._Y);
	rw->draw(circ);
};

AABB Player::GenAABB()
{
	return AABB(_Position._X, _Position._Y, _Size._X, _Size._Y);
}