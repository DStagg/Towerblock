#include "Player.h"

Player::Player()
{
	_Size = PairInt(32, 32);
};

Player::~Player()
{

};

void Player::Input()
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
};

void Player::Update(float dt) 
{
	Entity::Update(dt);

	if (_KnockbackTimer > 0.f)
		_KnockbackTimer -= dt;

};

void Player::Draw(sf::RenderWindow* rw)
{
	//	Draw main body
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Blue);
	circ.setRadius(16.f);
	circ.setOrigin(16.f, 16.f);
	circ.setPosition((float)_Position.GetX(), (float)_Position.GetY());
	rw->draw(circ);

	//	Indicate facing
	sf::CircleShape circ2;
	circ2.setRadius(2.5f);
	circ2.setFillColor(sf::Color::White);
	circ2.setOrigin(2.5f, 2.5f);
	circ2.setPosition(_Position.GetX() + (32.f * CalcXComp(_Facing)), _Position.GetY() + (32.f * CalcYComp(_Facing)));
	rw->draw(circ2);

};

bool Player::Knockback(Vec over)
{
	_Position -= over;
	if (_KnockbackTimer > 0.f)
		return false;
	_KnockbackTimer = 1.f;
	_HP -= 10;
	//Log("(" + FloatToString((float)_Position.GetX() + (over._X * 1.1f)) + "," + FloatToString((float)_Position.GetY() + (over._Y * 1.1f)) + ") - (" + FloatToString(over._X) + "," + FloatToString(over._Y) + ") * 1.1f = (" + FloatToString((float)_Position.GetX()) + "," + FloatToString((float)_Position.GetY()) + ")");
	return true;
};

CircleMask Player::GetMask()
{
	return CircleMask(Circle(_Position.GetX(), _Position.GetY(), 16));
};