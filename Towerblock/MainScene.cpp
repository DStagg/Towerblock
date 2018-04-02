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

	_DrawLog = false;

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

	Console::C()->Init(_Font, ConsoleTextSize, ConsoleLineLimit);

};
void MainScene::End()
{
	Console::C()->DumpLog("Testlog");
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

		}
		else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
			SetRunning(false);
		else if (Event.type == sf::Event::KeyPressed)
			switch (Event.key.code) 
			{
			case sf::Keyboard::F1:
				_DrawLog = !_DrawLog;
				break;
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

	float pSize = (_Player._Size._X + _Player._Size._Y) / 4.f;
	float eSize = (_Enemy._Size._X + _Enemy._Size._Y) / 4.f;
	if (CalcDistance(_Player._Position._X, _Player._Position._Y, _Enemy._Position._X, _Enemy._Position._Y) < pSize + eSize)
		_Player.Knockback();//	TODO: add proper, sensibly located collision detection between enemy and player
};
void MainScene::DrawScreen()
{
	_Window->setView(_CameraView);
	sf::Sprite temp = _CompositeTex.BuildSprite();
	_Window->draw(temp);

	_Player.Draw(_Window);
	_Enemy.Draw(_Window);

	//	Debug Draw Player
	DebugDrawAABB(_Player.GenAABB(), _Window);
	DebugDrawAABB(_Enemy.GenAABB(), _Window);

	//	Health Bar
	float barHeight = 50.f;
	sf::RectangleShape backBar;
	backBar.setSize(sf::Vector2f((float)_Window->getSize().x, barHeight));
	backBar.setPosition(0.f, _Window->getSize().y - barHeight);
	backBar.setFillColor(sf::Color(155, 155, 155));
	_Window->draw(backBar);
	
	sf::RectangleShape frontBar;
	frontBar.setPosition(0.f, _Window->getSize().y - barHeight);
	frontBar.setSize(sf::Vector2f(_Window->getSize().x * ((float)_Player._HP / 100.f), barHeight));
	frontBar.setFillColor(sf::Color::Red);
	_Window->draw(frontBar);
	
	if (_DrawLog)
		Console::C()->Draw(_Window);
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