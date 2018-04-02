#include "MainScene.h"

MainScene::MainScene(sf::RenderWindow* rw)
{
	_Window = rw;
};
MainScene::~MainScene()
{

};

void MainScene::Begin()
{
	_CameraView = _Window->getDefaultView();

	sf::Image img;
	img.loadFromFile("Tilesheet.png");
	std::map<int, PairInt> dic;
	dic[0] = PairInt(0, 0);
	dic[1] = PairInt(1, 0);
	dic[2] = PairInt(1, 0);
	dic[3] = PairInt(1, 1);
	CompositeBuilder builder(img,PairInt(32,32),dic);

	_Player._Position = PairFloat(100.f, 100.f);
	_Enemy._Position = PairFloat(200.f, 200.f);
	_Enemy._Velocity = PairFloat(70.f, 70.f);
	_Level.GenerateBox(20, 10);

	builder.BuildCompositeTex(_Level.GetGrid(), &_CompositeTex);

	_Font.loadFromFile("Roboto-Regular.ttf");
};
void MainScene::End()
{
	
};
void MainScene::Pause()
{

};
void MainScene::Resume()
{

};
void MainScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);
		else if (Event.type == sf::Event::MouseButtonPressed)
		{
			/*
			float heading = CalcHeading(_Player._Position._X, _Player._Position._Y, (float)sf::Mouse::getPosition(*_Window).x, (float)sf::Mouse::getPosition(*_Window).y);
			std::cout << "Heading  : " << heading << std::endl;
			std::cout << "- In rads: " << DegreeToRad(heading) << std::endl;
			std::cout << "- Y Comp.: " << CalcYComp(heading) << std::endl;
			std::cout << "- RYComp.: " << CalcYComp(DegreeToRad(heading)) << std::endl;
			std::cout << "0: " << DegreeToRad(0.f) << " |90: " << DegreeToRad(90.f) << " |180: " << DegreeToRad(180.f) << " |270: " << DegreeToRad(270.f) << std::endl;
			std::cout << "Cos: 0: " << CalcYComp(DegreeToRad(0.f)) << " |90: " << CalcYComp(DegreeToRad(90.f)) << " |180: " << CalcYComp(DegreeToRad(180.f)) << " |270: " << CalcYComp(DegreeToRad(270.f)) << std::endl;
			std::cout << "Cos(0): " << cosf(0.f) << std::endl;
			std::cout << "-----------" << std::endl;
			*/
			std::cout << "Up: " << CalcAngle(100.f, 100.f, 100.f, 0.f) << " ( " << CalcXComp(CalcAngle(100.f, 100.f, 100.f, 0.f)) << "," << CalcYComp(CalcAngle(100.f, 100.f, 100.f, 0.f)) << ")" << std::endl;
			std::cout << "Ri: " << CalcAngle(100.f, 100.f, 200.f, 100.f) << " ( " << CalcXComp(CalcAngle(100.f, 100.f, 200.f, 100.f)) << "," << CalcYComp(CalcAngle(100.f, 100.f, 200.f, 100.f)) << ")" << std::endl;
			std::cout << "Dn: " << CalcAngle(100.f, 100.f, 100.f, 200.f) << " ( " << CalcXComp(CalcAngle(100.f, 100.f, 100.f, 200.f)) << "," << CalcYComp(CalcAngle(100.f, 100.f, 100.f, 200.f)) << ")" << std::endl;
			std::cout << "Le: " << CalcAngle(100.f, 100.f, 0.f, 100.f) << " ( " << CalcXComp(CalcAngle(100.f, 100.f, 0.f, 100.f)) << "," << CalcYComp(CalcAngle(100.f, 100.f, 0.f, 100.f)) << ")" << std::endl;
			std::cout << "NW: " << CalcAngle(100.f, 100.f, 0.f, 0.f) << " ( " << CalcXComp(CalcAngle(100.f, 100.f, 0.f, 0.f)) << "," << CalcYComp(CalcAngle(100.f, 100.f, 0.f, 0.f)) << ")" << std::endl;
			std::cout << "-----------" << std::endl;
		}
		else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
			SetRunning(false);
		else if (Event.type == sf::Event::KeyPressed)
			switch (Event.key.code) 
			{
			case sf::Keyboard::Left:
				_CameraView.move(-32.f, 0.f);
				break;
			case sf::Keyboard::Right:
				_CameraView.move(32.f, 0.f);
				break;
			case sf::Keyboard::Down:
				_CameraView.move(0.f, 32.f);
				break;
			case sf::Keyboard::Up:
				_CameraView.move(0.f, -32.f);
				break;
			case sf::Keyboard::BackSpace:
				_CameraView = _Window->getDefaultView();
				break;
			default:
				break;
			}
	}
	//_Player._Facing = CalcHeading(_Player._Position._X, _Player._Position._Y, (float)sf::Mouse::getPosition(*_Window).x, (float)sf::Mouse::getPosition(*_Window).y);
	_Player._Facing = CalcHeading(_Player._Position._X, _Player._Position._Y, _Enemy._Position._X, _Enemy._Position._Y);
	_Player.Update(dt);
	_Enemy.Update(dt);
	CollisionResults pRes = _Level.WallCollision(&_Player);
	CollisionResults eRes = _Level.WallCollision(&_Enemy);
	if (pRes._Collided)
	{
		_Player._Position._X -= _Player._Velocity._X * dt;
		_Player._Position._Y -= _Player._Velocity._Y * dt;
		_Player._Velocity = PairFloat(0.f, 0.f);
	}
	if (eRes._Collided)
	{
		_Enemy._Position._X -= _Enemy._Velocity._X * dt;
		_Enemy._Position._Y -= _Enemy._Velocity._Y * dt;
		_Enemy._Velocity._X = -_Enemy._Velocity._X;
		_Enemy._Velocity._Y = -_Enemy._Velocity._Y;
	}
};
void MainScene::DrawScreen()
{
	_Window->setView(_CameraView);
	sf::Sprite temp = _CompositeTex.BuildSprite();
	_Window->draw(temp);

//	_Player.Draw(_Window);
//	_Enemy.Draw(_Window);

	//	Debug Draw Player
//	DebugDrawAABB(_Player.GenAABB(), _Window);
//	DebugDrawAABB(_Enemy.GenAABB(), _Window);

	sf::RectangleShape square;
	square.setSize(sf::Vector2f(16.f, 16.f));
	square.setOrigin(8.f, 8.f);
	square.setPosition(320.f, 320.f);
	square.setFillColor(sf::Color::White);
	_Window->draw(square);
	
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(16.f, 16.f));
	rect.setFillColor(sf::Color::Magenta);
	rect.setPosition(320.f + (100.f * CalcXComp(CalcHeading(320.f, 320.f, sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y))), 320.f + (100.f * CalcYComp(CalcHeading(320.f, 320.f, sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y))));	
	_Window->draw(rect);

	sf::Text text;
	text.setFont(_Font);

	text.setString("Mouse at: (" + FloatToString(sf::Mouse::getPosition(*_Window).x) + "," + FloatToString(sf::Mouse::getPosition(*_Window).y) + ")");
	text.setPosition(0.f, 0.f);
	_Window->draw(text);

	text.setString("Difference: " + FloatToString(CalcDistance(320.f, 320.f, sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y)) + " (" + FloatToString(sf::Mouse::getPosition(*_Window).x - 320.f) + "," + FloatToString(sf::Mouse::getPosition(*_Window).y - 320.f) + ")");
	text.setPosition(0.f, 50.f);
	_Window->draw(text);

	text.setString("Angle: " + FloatToString(CalcAngle(320.f, 320.f, sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y)) + " | " + FloatToString(CalcAngle(320.f, 320.f, sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y)*180.f / Pi) );
	text.setPosition(0.f, 100.f);
	_Window->draw(text);

	text.setString("Heading: " + FloatToString(CalcHeading(320.f, 320.f, sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y)) + " | " + FloatToString(CalcHeading(320.f, 320.f, sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y) * 180.f / Pi) );
	text.setPosition(0.f, 150.f);
	_Window->draw(text);

	text.setString("Components: (" + FloatToString(CalcXComp(CalcHeading(320.f, 320.f, sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y))) + "," + FloatToString(CalcYComp(CalcHeading(320.f, 320.f, sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y))) + ")");
	text.setPosition(0.f, 200.f);
	_Window->draw(text);
};

void DebugDrawAABB(AABB box, sf::RenderWindow* rw)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(box._Width, box._Height));
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color::Green);
	rect.setFillColor(sf::Color::Transparent);
	rect.setPosition(box._X, box._Y);
	rw->draw(rect);

};