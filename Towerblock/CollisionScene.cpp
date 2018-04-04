#include "CollisionScene.h"

CollisionScene::CollisionScene(sf::RenderWindow* rw)
{
	_Window = rw;
};
CollisionScene::~CollisionScene()
{

};

void CollisionScene::Begin()
{
	_CameraView = _Window->getDefaultView();

	_DrawLog = false;

	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");

	Console::C()->Init(_Font, ConsoleTextSize, ConsoleLineLimit);

	_Box1 = AABB(50, 50, 50, 100);
	_Box2 = AABB(300, 200, 100, 50);
	_Circ1 = Circle(100, 300, 100);
	_Circ2 = Circle(320, 320, 50);

};
void CollisionScene::End()
{
	Console::C()->DumpLog("Collision Tests ended.");
};
void CollisionScene::Pause()
{

};
void CollisionScene::Resume()
{

};
void CollisionScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);
		else if (Event.type == sf::Event::MouseButtonPressed)
		{
			if (Event.mouseButton.button == sf::Mouse::Button::Left)
			{
				//_Player._Position.set(sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y);
			}
			else if (Event.mouseButton.button == sf::Mouse::Button::Right)
			{

			}
		}
		else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
			SetRunning(false);
		else if (Event.type == sf::Event::KeyPressed)
			switch (Event.key.code)
			{
			case sf::Keyboard::F1:
				_DrawLog = !_DrawLog;
				break;
			case sf::Keyboard::Num1:
				_Choice = 0;
				break;
			case sf::Keyboard::Num2:
				_Choice = 1;
				break;
			case sf::Keyboard::Num3:
				_Choice = 2;
				break;
			case sf::Keyboard::Num4:
				_Choice = 3;
				break;
			case sf::Keyboard::Num5:
				_Choice = 4;
				break;
			default:
				break;
			}
	}

	PairInt mousePos(sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y);
	if (_Choice == 0)
	{
		_Box1._X = mousePos._X;
		_Box1._Y = mousePos._Y;
	}
	else if (_Choice == 1)
	{
		_Box2._X = mousePos._X;
		_Box2._Y = mousePos._Y;
	}
	else if (_Choice == 2)
	{
		_Circ1._X = mousePos._X;
		_Circ1._Y = mousePos._Y;
	}
	else if (_Choice == 3)
	{
		_Circ2._X = mousePos._X;
		_Circ2._Y = mousePos._Y;
	}

};
void CollisionScene::DrawScreen()
{
	_Window->setView(_CameraView);

	CollisionResults res = SATCheckAABBtoAABB(_Box1, _Box2);
	if (res._Collided)
	{
		DebugDrawAABB(_Box1, _Window, sf::Color::Blue);
		Log("[" + FloatToString(res._Overlap._X) + "," + FloatToString(res._Overlap._Y) + "]");
	}
	else
		DebugDrawAABB(_Box1, _Window, sf::Color::Green);
	DebugDrawAABB(_Box2, _Window, sf::Color::Yellow);
	CollisionResults res2 = SimpleAABBtoCircle(_Box1, _Circ1);
	if (res2._Collided)
	{
		DebugDrawCirc(_Circ1, _Window, sf::Color::Cyan);
	}
	else
		DebugDrawCirc(_Circ1, _Window, sf::Color::White);
	DebugDrawCirc(_Circ2, _Window, sf::Color::Red);



	_Window->setView(_Window->getDefaultView());

	if (_DrawLog)
		Console::C()->Draw(_Window);
};
