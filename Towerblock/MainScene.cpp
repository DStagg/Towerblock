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
	_Level.GenerateBox(20, 10);

	builder.BuildCompositeTex(_Level.GetGrid(), &_CompositeTex);
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

	_Player.Update(dt);
	if (_Level.WallCollision(&_Player))
	{
		_Player._Position._X -= _Player._Velocity._X * dt;
		_Player._Position._Y -= _Player._Velocity._Y * dt;
		_Player._Velocity = PairFloat(0.f, 0.f);
	}
};
void MainScene::DrawScreen()
{
	_Window->setView(_CameraView);
	sf::Sprite temp = _CompositeTex.BuildSprite();
	_Window->draw(temp);

	_Player.Draw(_Window);

	//	Debug Draw Player
	DebugDrawAABB(_Player.GenAABB(), _Window);
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