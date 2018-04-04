#include "Player.h"

Player::Player()
{
	_Size = PairInt(32, 32);
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

	_Position += _Velocity * dt;

	if (_KnockbackTimer > 0.f)
		_KnockbackTimer -= dt;

	_Mask._Mask = Circle(_Position.GetX(), _Position.GetY(), 16);
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

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(5.f, 5.f));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(_Position.GetX() + circ.getRadius() + (32.f * CalcXComp(_Facing)), _Position.GetY() + circ.getRadius() + (32.f * CalcYComp(_Facing)));
	rw->draw(rect);

};

void Player::Knockback(Vec over)
{
	_Position -= over * 2.f;
	if (_KnockbackTimer > 0.f)
		return;
	_KnockbackTimer = 1.f;
	_HP -= 10;
	Log("(" + FloatToString((float)_Position.GetX() + (over._X * 1.1f)) + "," + FloatToString((float)_Position.GetY() + (over._Y * 1.1f)) + ") - (" + FloatToString(over._X) + "," + FloatToString(over._Y) + ") * 1.1f = (" + FloatToString((float)_Position.GetX()) + "," + FloatToString((float)_Position.GetY()) + ")");
	
	
};

CircleMask& Player::GetMask()
{
	return _Mask;
};