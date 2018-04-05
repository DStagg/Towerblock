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

	_ImgMan.SetDirectory("Resources");
	_ImgMan.LoadTextureFromFile("Tilesheet", "Tilesheet.png");
	
	sf::Image img = _ImgMan.GetTexturePntr("Tilesheet")->copyToImage();
	std::map<int, PairInt> dic;
	dic[0] = PairInt(0, 0);
	dic[1] = PairInt(1, 0);
	dic[2] = PairInt(1, 0);
	dic[3] = PairInt(1, 1);
	CompositeBuilder builder(img,PairInt(32,32),dic);

	_Level.GenerateBox(20, 10);
	_Level.GetGrid().SetCell(10, 5, 1);

	builder.BuildCompositeTex(_Level.GetGrid(), &_CompositeTex);

	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");

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
			if (Event.mouseButton.button == sf::Mouse::Button::Left)
			{
				//_Player._Position.set(sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y);
			}
			else if (Event.mouseButton.button == sf::Mouse::Button::Middle)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
					_Level.GetPlayer()._Position.Set(sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y);
				else
					_Level.Spawn(sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y);

			//Log("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890!'£$%^&*()");
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
				//_CameraView.move(-32.f, 0.f);
				_Level.Spawn(_Level.GetPlayer()._Position.GetX() + 150, _Level.GetPlayer()._Position.GetY(), -100, 0);
				break;
			case sf::Keyboard::Right:
				//_CameraView.move(32.f, 0.f);
				_Level.Spawn(_Level.GetPlayer()._Position.GetX() - 150, _Level.GetPlayer()._Position.GetY(), 100, 0);
				break;
			case sf::Keyboard::Down:
				//_CameraView.move(0.f, 32.f);
				_Level.Spawn(_Level.GetPlayer()._Position.GetX(), _Level.GetPlayer()._Position.GetY() + 150, 0, -100);
				break;
			case sf::Keyboard::Up:
				//_CameraView.move(0.f, -32.f);
				_Level.Spawn(_Level.GetPlayer()._Position.GetX(), _Level.GetPlayer()._Position.GetY() - 150, 0, 100);
				break;
			case sf::Keyboard::BackSpace:
				_CameraView = _Window->getDefaultView();
				break;
			default:
				break;
			}
	}

	_Level.Update(dt, _Window);

};
void MainScene::DrawScreen()
{
	_Window->setView(_CameraView);

	sf::Sprite temp = _CompositeTex.BuildSprite();
	_Window->draw(temp);

	_Level.Draw(_Window);

	_Window->setView(_Window->getDefaultView());
	
	//	Health Bar
	float barHeight = 50.f;
	sf::RectangleShape backBar;
	backBar.setSize(sf::Vector2f((float)_Window->getSize().x, barHeight));
	backBar.setPosition(0.f, _Window->getSize().y - barHeight);
	backBar.setFillColor(sf::Color(155, 155, 155));
	_Window->draw(backBar);
	
	sf::RectangleShape frontBar;
	frontBar.setPosition(0.f, _Window->getSize().y - barHeight);
	frontBar.setSize(sf::Vector2f(_Window->getSize().x * ((float)_Level.GetPlayer()._HP / 100.f), barHeight));
	frontBar.setFillColor(sf::Color::Red);
	_Window->draw(frontBar);

	//	Fire Bar
	float fireBarHeight = 10.f;
	sf::RectangleShape fireBar;
	fireBar.setSize(sf::Vector2f((float)_Window->getSize().x * (_Level.GetFireTimer() / 1.f), fireBarHeight));
	fireBar.setPosition(0.f, _Window->getSize().y - (barHeight + fireBarHeight));
	fireBar.setFillColor(sf::Color::White);
	_Window->draw(fireBar);
	
	if (_DrawLog)
		Console::C()->Draw(_Window);
};
