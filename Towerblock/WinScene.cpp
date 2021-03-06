#include "WinScene.h"

WinScene::WinScene(sf::RenderWindow* rw) : SFMLScene(rw)
{
	
};

WinScene::~WinScene()
{

};

void WinScene::Begin()
{
	_Window->setView(_Window->getDefaultView());
	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");
};

void WinScene::End()
{

};

void WinScene::Pause()
{

};

void WinScene::Resume()
{

};

void WinScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if (Event.type == sf::Event::KeyPressed)
			if (Event.key.code == sf::Keyboard::Key::Escape)
				GetManager()->Quit();
	}
};

void WinScene::DrawScreen()
{
	_Window->setView(_Window->getDefaultView());

	sf::Text winMsg;
	winMsg.setString("Winner!");
	winMsg.setFont(_Font);
	winMsg.setFillColor(sf::Color::White);
	winMsg.setPosition((_Window->getSize().x - winMsg.getGlobalBounds().width) / 2.f, (_Window->getSize().y - winMsg.getGlobalBounds().height) / 2.f);
	_Window->draw(winMsg);
};