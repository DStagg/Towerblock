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

//	_Facing = CalcHeading(_Position._X, _Position._Y, (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y);

};

void Player::Draw(sf::RenderWindow* rw)
{
	//	Draw main body
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Blue);
	circ.setRadius(((float)_Size._X + (float)_Size._Y) / 4.f);
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	circ.setPosition(_Position._X + circ.getRadius(), _Position._Y + circ.getRadius());
	rw->draw(circ);

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(5.f, 5.f));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(_Position._X + circ.getRadius() + (32.f * CalcXComp(_Facing)), _Position._Y + circ.getRadius() + (32.f * CalcYComp(_Facing)));
	rw->draw(rect);

};

AABB Player::GenAABB()
{
	return AABB(_Position._X, _Position._Y, _Size._X, _Size._Y);
}