#include "MainScene.h"

MainScene::MainScene(sf::RenderWindow* rw) : SFMLScene(rw)
{
	
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
	
	CompositeBuilder builder(img,PairInt(32,32));

	_Level.Load("Level.sav");

	builder.BuildCompositeTex(_Level.BuildSpriteCoordGrid(), &_CompositeTex);

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
			GetManager()->Quit();
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
			GetManager()->Quit();
		else if (Event.type == sf::Event::KeyPressed)
			switch (Event.key.code) 
			{
			case sf::Keyboard::F1:
				_DrawLog = !_DrawLog;
				break;
			case sf::Keyboard::P:
				_Paused = !_Paused;
				break;
			case sf::Keyboard::Num1:
				_Level.Save("Save.sav");
				break;
			case sf::Keyboard::Num2:
				_Level.Load("Save.sav");
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

	if (!_Paused)
		_Level.Update(dt, _Window);

	if (_Level.CountEnemies() == 0)
	{
		GetManager()->PushScene(new WinScene(_Window), new FadeTransition(_Window, 1.f));
	}
	else if (_Level.GetPlayer()._HP <= 0)
	{
		GetManager()->PushScene(new LoseScene(_Window), new FadeTransition(_Window, 1.f));
	}
	//	TODO: fix enemy knockback
	//	TODO: grab world mouse coordinates rather than screen (even if screen is relative to the window)
	//	Asymptotic Averaging
	//	Ratio can be anything  - just make sure it equals 1.f. Lower followFactor = faster zoom.
	float followFactor = 0.99f;
	_CameraView.setCenter((_CameraView.getCenter().x * followFactor) + (_Level.GetPlayer()._Position.GetX() * (1.f - followFactor)), (_CameraView.getCenter().y * followFactor) + (_Level.GetPlayer()._Position.GetY() * (1.f - followFactor)) );
};
void MainScene::DrawScreen()
{
	_Window->setView(_CameraView);

	sf::Sprite temp = _CompositeTex.BuildSprite();
	_Window->draw(temp);

	_Level.Draw(_Window);

	//	Screen Flash
	if (_Level.GetFlashTimer() > 0.f)
	{
		sf::RectangleShape flash;
		flash.setSize(sf::Vector2f((float)_Window->getSize().x, (float)_Window->getSize().y));
		flash.setPosition(0.f, 0.f);
		flash.setFillColor(sf::Color(255, 255, 255, sf::Uint8(255 * (1 - (_Level.GetFlashTimer() / _Level.GetFlashDuration())))));
		_Window->draw(flash);
	}

	_Window->setView(_Window->getDefaultView());

	//	Ammo Count
	sf::Text amm;
	amm.setFont(_Font);
	amm.setFillColor(sf::Color::White);
	amm.setPosition(5.f, 5.f);
	amm.setString("LClick: " + _Level.GetGun(0)->_Name + " : " + IntToString(_Level.GetGun(0)->_CurrentAmmo) + "/" + IntToString(_Level.GetGun(0)->_MaxAmmo));
	_Window->draw(amm);

	amm.setPosition(5.f, amm.getGlobalBounds().top + amm.getGlobalBounds().height + 5.f);
	amm.setString("RClick: " + _Level.GetGun(1)->_Name + " : " + IntToString(_Level.GetGun(1)->_CurrentAmmo) + "/" + IntToString(_Level.GetGun(1)->_MaxAmmo));
	_Window->draw(amm);
	
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
